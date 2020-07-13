//finding a single tour for a board

object Knight {

type Pos = (Int, Int)    // a position on a chessboard 
type Path = List[Pos]    // a path...a list of positions

	def main(args: Array[String]){
		
		println(first_tour(4,List[Pos]((0,0))))
		

	}

	def first(xs: List[Pos], f: Pos => Option[Path]) : Option[Path] = {
		if(xs == Nil){
			(None)
		}
		else{
			(calc_f(xs, f, 0))	
		}
	}

	def calc_f (xs: List[Pos], f: Pos => Option[Path], place : Int ) : Option[Path] = {
		if(place == xs.size){
			(None)
		}else {
			val res = f(xs(place))
			if (!res.isDefined){
				(calc_f(xs, f, place+1))
			}
			else{
				(res)
			}
		}
	}



def first_tour(dim: Int, path: Path,  f: Pos => Option[Path]) : Option[Path] = {

	if(path.size == 0){
		val start =  for (i <- (0 to dim-1).toList;
					j <- (0 to dim-1).toList; if path.find(_ == (i,j)) == None )  yield ((i,j))
		val allints = for ( n <- start ) yield {
					val list = List[List[Pos]](path, List[Pos]((n)))
					val finalpos = first_pos(dim, list.flatten, n, f)
					finalpos
		}
		
		val finalval = allints.find(_!= None)

		if (finalval.size > 0){
			(finalval.get)
		}
		else{
			(None)
		}

		}else{
			
		( first_pos(dim, path, path(path.size-1), f) ) 	

		}	

	}

def first_pos(dim: Int, path: Path, x : Pos,  f: Pos => Option[Path] ) : Option[Path] = {
	val fx = (tempPos: Pos) =>f(tempPos)
	if(path.size == (dim * dim)){
		val eppa = List[Pos]()
		val templist = List[Path](path,eppa)
		(templist.find(_ != Nil ))
		}
		else {
			val moves = fx(x)
			if( moves == None){
				(None) 
			}
			else{
				val allints = for (n <- moves) yield {
					val list = List[Path](path, n)
					val finalpos = first_pos(dim, list.flatten, n(0), f)
					finalpos
				}
				val finalval = allints.find(_ != None)
				if(finalval.size > 0){
					(finalval.get)
				}
				else{
					(None)
				}
			}
		}

	}
 

}
