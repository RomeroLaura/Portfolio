from axelrod import Player
from axelrod.action import Action, actions_to_str
C, D = Action.C, Action.D

class Mensa(Player):
    """
    A player starts by Defecting and continues to defect on every odd turn. On 
    even turns, if the previous move by the oponent was to cooperate, it 
    also cooperates.

    Names

    - Mensa : [New source]_  replace with proper code e.g TitForTat: [Axelrod1980]_
    - TBA to References : https://www.mathworks.com/matlabcentral/fileexchange/27611-iterated-prisoner-s-dilemma
    
    """

    name = 'Mensa'
    classifier = {
        'memory_depth': 1,  
        'stochastic': False,
        'inspects_source': False,
        'manipulates_source': False,
        'manipulates_state': False
    }

    def strategy(self, opponent):
        #Check if even and the previous move was to cooperate
        if len(self.history) % 2 == 0 and opponent.history[-1] == C:
            return C
        #else defect
        return D