#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject * array_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
static PyObject * populate_empty( PyObject *obj);
static PyObject *array_alloc(PyTypeObject *type, Py_ssize_t NPY_UNUSED(nitems));

typedef int32_t intp_t;

/*MyArray struct
 *  Holds the parts of the array itself
 *
 */
typedef struct tagMyArray {
    PyObject_HEAD
    /* required */
    char *data;
    /* dimensions in the array data structure */
    int nd;
    /* the size of each dimension, an array */
    intp_t *dimensions;
    /* unused but will be used when extended */
    intp_t *strides;
    PyObject *base;
    /* required */
    int flags;
    /* required */
    PyObject *weakreflist;
} MyArray;


#define SIZEOF_ARRAYOBJECT (sizeof(MyArray))

/*array_new
 *  Create a new instance of an array
 *  @param: dim sets nd, s1 and s2 set dimensions
 *  @return: returns MyArray object
 */
static PyObject *
array_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    MyArray *self;
    int * dim, s1, s2;
    int success;

    self = (MyArray *) type->tp_alloc(type, 0);
    success  = PyArg_ParseTuple(args, "iii", &dim, &s1, &s2);

    self->nd = dim;
    self->nd = 2; //Hardcode two dimension for now

    intp_t steps[2] = {s1,s2};
    self->dimensions = steps;

    int i = 0;
    int size = sizeof(intp_t*);
    for (i = 0; i < self->nd; i++){
      size = size* steps[i];
    }
    self->base = malloc(size);

    self = populate_empty(self);

    return (PyObject *) self;
};



/*populate_empty
 *  fills an array with 0 objects
 *  @params: none
 *  @return: returns MyArray object
 */
static PyObject * populate_empty(PyObject *obj){

  MyArray * fa = (MyArray *) obj;
  intp_t *steps = fa->dimensions;
  intp_t* ptr = fa->base;

  int size = 1;
  int i = 0;
  for (i = 0; i < fa->nd; i++)
  {
    intp_t temp =  (*steps);
    size = size  *  temp;
    steps++;
  }

  for(i = 0; i < size; i++){
    (intp_t) ptr = 0;
    ptr = ptr + sizeof(intp_t);
  }
  return (PyObject *) fa;
};


/*array_alloc
 *  Allocator function for MyArray
 * @params: none
 * @return: returns PyObject
 */
static PyObject *
array_alloc(PyTypeObject *type, Py_ssize_t NPY_UNUSED(nitems))
{

    PyObject *obj = PyObject_Malloc(type->tp_basicsize);
    PyObject_Init(obj, type);
    return obj;
};

/*MyArrayType struct
 * the basic usabiliy functions of MyArray
 *
 */
static PyTypeObject MyArrayType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "custom.array",
    .tp_basicsize = SIZEOF_ARRAYOBJECT,
    .tp_flags =(Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE),
    .tp_new = (newfunc)array_new,
    .tp_alloc = (allocfunc)array_alloc,

    /*
     *TODO: next functions to complete
     *.tp_dealloc = (destructor)array_dealloc,
     *.tp_richcompare = (richcmpfunc)array_richcompare,
     *.tp_iter = (getiterfunc)array_iter,
     *.tp_methods = array_methods,
     *.tp_getset = array_getsetlist,
     *.tp_free = (freefunc)array_free,*/
};

/*custommodule + PyInit_custom
 *  basic module initialization
 */
static PyModuleDef custommodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "custom",
    .m_doc = "A preliminary attempt to add personal arrays to python.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_custom(void)
{
    PyObject *m;
    if (PyType_Ready(&MyArrayType) < 0)
        return NULL;

    m = PyModule_Create(&custommodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&MyArrayType);
    if (PyModule_AddObject(m, "array", (PyObject *) &MyArrayType) < 0) {
        Py_DECREF(&MyArrayType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
