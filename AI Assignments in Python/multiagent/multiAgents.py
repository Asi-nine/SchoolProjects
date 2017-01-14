# multiAgents.py
# --------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
  """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
  """


  def getAction(self, gameState):
    """
    You do not need to change this method, but you're welcome to.

    getAction chooses among the best options according to the evaluation function.

    Just like in the previous project, getAction takes a GameState and returns
    some Directions.X for some X in the set {North, South, West, East, Stop}
    """
    # Collect legal moves and successor states
    legalMoves = gameState.getLegalActions()

    # Choose one of the best actions
    scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
    bestScore = max(scores)
    bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
    chosenIndex = random.choice(bestIndices) # Pick randomly among the best

    "Add more of your code here if you want to"

    return legalMoves[chosenIndex]

  def evaluationFunction(self, currentGameState, action):
    """
    Design a better evaluation function here.

    The evaluation function takes in the current and proposed successor
    GameStates (pacman.py) and returns a number, where higher numbers are better.

    The code below extracts some useful information from the state, like the
    remaining food (oldFood) and Pacman position after moving (newPos).
    newScaredTimes holds the number of moves that each ghost will remain
    scared because of Pacman having eaten a power pellet.

    Print out these variables to see what you're getting, then combine them
    to create a masterful evaluation function.
    """
    # Useful information you can extract from a GameState (pacman.py)
    successorGameState = currentGameState.generatePacmanSuccessor(action)
    newPos = successorGameState.getPacmanPosition()
    #print newPos 
    oldFood = currentGameState.getFood().asList()
    #print oldFood
    newGhostStates = successorGameState.getGhostStates()
    #print newGhostStates
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
    #print newScaredTimes

    "*** YOUR CODE HERE ***"
    #AUTHOR: PETER VALOVCIK

    #set up variable for ghost value portion of the return
    ghostReturn = 0

    #set a high ghost distance to begin so that that any lower real one will be used
    ghostMinDistance = 1000
    #Loop through the possible new ghost positions and get the manhattan distance between them and pacman's new position
    for ghostState in newGhostStates:
      ghostManhattanDistance = util.manhattanDistance(newPos, ghostState.getPosition())
      if ghostManhattanDistance < ghostMinDistance:
        ghostMinDistance = ghostManhattanDistance
        #set a leash so that pacman doesn't want to be too far from the ghost (this helped with not having
        #pacman sit in corners as much)
        if ghostManhattanDistance > 6:
          ghostReturn = -4000
        #make sure that pacman wants to never be in the same spac eas the ghost unless the ghost is scared
        elif ghostManhattanDistance == 0:
          if ghostState.scaredTimer > 0:
            ghostReturn = 5000
          else:
            ghostReturn = -4000
        #encourage pacman to move towards a ghost when it is scared, and discourage getting close when it is not
        else:
          if ghostState.scaredTimer > 0:
            ghostReturn = 4000.0/ghostManhattanDistance
          else:
           ghostReturn = -100.0/ghostManhattanDistance   

    #set up vaiable for food value portion of the return
    foodReturn = 0
    #set a high food distance to begin so that that any lower real one will be used    
    foodMinDistance = 1000
    #Loop through the possible food positions and get the manhattan distance between them and pacman's new position    
    for food in oldFood:
      foodManhattanDistance = util.manhattanDistance(newPos, food) 
      if foodManhattanDistance < foodMinDistance:
        foodMinDistance = foodManhattanDistance
        #reward pacman if his next position is on top of food
        if foodManhattanDistance == 0:
          foodReturn = 50
        #encourage pacman to make the distance between him and food smaller
        else: 
          foodReturn = 20.0/foodManhattanDistance 

    #set up vaiable for capsule value portion of the return
    capsuleReturn = 0
    #need to get capsule positions
    oldCapsule = currentGameState.getCapsules()
    #set a high capsule distance to begin so that that any lower real one will be used        
    capsuleMinDistance = 1000
    #Loop through the possible capsule positions and get the manhattan distance between them and pacman's new position        
    for capsules in oldCapsule:
      capsuleManhattanDistance = util.manhattanDistance(newPos, capsules)
      if capsuleManhattanDistance < capsuleMinDistance:
        capsuleMinDistance = capsuleManhattanDistance
        #reward pacman if his next position is on top of capsule (more than food since it gives more points)        
        if capsuleManhattanDistance == 0:
          capsuleReturn = 95
        #encourage pacman to make the distance between him and capsule smaller (more than food since it gives more points)  
        else: 
          capsuleReturn = 40.0/capsuleManhattanDistance

    return ghostReturn + foodReturn + capsuleReturn + successorGameState.getScore()


def scoreEvaluationFunction(currentGameState):
  """
    This default evaluation function just returns the score of the state.    ghostMinDistance = 1000
    for ghostState in newGhostStates:
        ghostManhattanDistance = util.manhattanDistance(newPos, ghostState.getPosition())
        if ghostManhattanDistance < ghostMinDistance:
            ghostMinDistance = ghostManhattanDistance
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
  """
  return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
  """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
  """

  def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
    self.index = 0 # Pacman is always agent index 0
    self.evaluationFunction = util.lookup(evalFn, globals())
    self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
  """
    Your minimax agent (question 2)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action from the current gameState using self.depth
      and self.evaluationFunction.

      Here are some method calls that might be useful when implementing minimax.

      gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

      Directions.STOP:
        The stop direction, which is always legal

      gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

      gameState.getNumAgents():
        Returns the total number of agents in the game
    """
    "*** YOUR CODE HERE ***"
    #AUTHOR: PETER VALOVCIK

    return self.finalDecision(gameState)

  #function to get the choice maximum makes with alpha beta pruning
  def maximumChoice(self, gameState, depth):

    if depth == (self.depth - 1) or gameState.isLose() or gameState.isWin():
      return self.evaluationFunction(gameState)

    #get the legal moves of pacman
    legalMoves = gameState.getLegalActions(0)

    #define the v to be a large negative number since it is supposed to be negative infinity 
    v = -100000000

    for move in legalMoves:
      #ignore stop direction
      if move != Directions.STOP:
        #get the successors for pacman's moves other than stop
        successorStates = gameState.generateSuccessor(0, move)
        #get the max between the min of successor states and the current max
        v = max(v, self.minimumChoice(successorStates, depth, 1))

    return v

      #function to get the choice minimum makes 
  def minimumChoice(self, gameState, depth, numberOfGhost):

    #get the number of total agents
    numAgents = gameState.getNumAgents()

    #first check for and 'end' state((bottom depth; loss or win) then return the UTILITY(state)
    if depth == (self.depth - 1) or gameState.isLose() or gameState.isWin():
      return self.evaluationFunction(gameState)

    #get the legal moves of ghost
    legalMoves = gameState.getLegalActions(numberOfGhost)

    #define the v to be a large positive number since it is supposed to be infinity 
    v = 100000000

    for move in legalMoves:
      #ignore stop direction
      if move != Directions.STOP:
        #get the successors for ghost's moves other than stop
        successorStates = gameState.generateSuccessor(1, move)
        #get the min between the max of successor states and the current min
        #written generically so that it will work for more tha one ghost
        if numberOfGhost == numAgents - 1:
          #last (or only) ghost
          v = min(v, self.maximumChoice(successorStates, depth + 1))
        else:
          #need to check more ghosts for potential min
          v = min(v, self.minimumChoice(successorStates, depth, numberOfGhost + 1))    

    return v

  #function to make a decision at the root of the tree(initiates a cal to maximumChoice which then states
  # the recursion between min and max)
  def finalDecision(self, gameState):

    #get the legal moves for Pacman
    legalMoves = gameState.getLegalActions(0)

    #define the v to be a large negative number since it is supposed to be negative infinity 
    v = -100000000

    #set up a variable to hold the action from the max during the loop
    decisiveMove = "Directions.STOP"

    for move in legalMoves:
      #ignore stop direction
      if move != Directions.STOP:
        #get the successors for moves other than stop
        successorStates = gameState.generateSuccessor(0, move)
        #keep track of the previous v value for comparison
        oldV = v
        #get the max between the min of successor states and the current max
        v = max(v, self.minimumChoice(successorStates, 0, 1))
        #if the current v is the new max, need to update the decision
        if oldV < v:
          decisiveMove = move

    return decisiveMove

class AlphaBetaAgent(MultiAgentSearchAgent):
  """
    Your minimax agent with alpha-beta pruning (question 3)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action using self.depth and self.evaluationFunction
    """
    "*** YOUR CODE HERE ***"
    #AUTHOR: PETER VALOVCIK

    return self.finalDecision(gameState)

  #function to get the choice maximum makes with alpha beta pruning
  def maximumChoice(self, gameState, depth, alpha, beta):

    #first check for and 'end' state((bottom depth; loss or win) then return the UTILITY(state)
    if depth == (self.depth - 1) or gameState.isLose() or gameState.isWin():
      return self.evaluationFunction(gameState)

    #get the legal moves of pacman
    legalMoves = gameState.getLegalActions(0)

    #define the v to be a large negative number since it is supposed to be negative infinity 
    v = -100000000

    for move in legalMoves:
      #ignore stop direction
      if move != Directions.STOP:
        #get the successors for pacman's moves other than stop
        successorStates = gameState.generateSuccessor(0, move)
        #get the max between the min of successor states and the current max
        v = max(v, self.minimumChoice(successorStates, depth, 1, alpha, beta))

        #can return v if it is less than or equal to alpha since it will not affect alpha further at that point.
        if v >= beta:
          return v;

        #set the alpha to the max if it's bigger than the current alpha
        alpha = max(v, alpha)


    return v

      #function to get the choice minimum makes 
  def minimumChoice(self, gameState, depth, numberOfGhost, alpha, beta):

    #get the number of total agents
    numAgents = gameState.getNumAgents()

    #first check for and 'end' state((bottom depth; loss or win) then return the UTILITY(state)
    if depth == (self.depth - 1) or gameState.isLose() or gameState.isWin():
      return self.evaluationFunction(gameState)

    #get the legal moves of ghost
    legalMoves = gameState.getLegalActions(numberOfGhost)

    #define the v to be a large positive number since it is supposed to be infinity 
    v = 100000000

    for move in legalMoves:
      #ignore stop direction
      if move != Directions.STOP:
        #get the successors for ghost's moves other than stop
        successorStates = gameState.generateSuccessor(1, move)
        #get the min between the max of successor states and the current min
        #written generically so that it will work for more tha one ghost
        if numberOfGhost == numAgents - 1:
          #last (or only) ghost
          v = min(v, self.maximumChoice(successorStates, depth + 1, alpha, beta))
        else:
          #need to check more ghosts for potential min
          v = min(v, self.minimumChoice(successorStates, depth, numberOfGhost + 1, alpha, beta))

        #can return v if it is less than or equal to alpha since it will not affect alpha further at that point.
        if v <= alpha:
          return v

        #set the beta to the min if it's bigger than the current beta        
        beta = min(v, beta)             

    return v

  #function to make a decision at the root of the tree(initiates a cal to maximumChoice which then states
  # the recursion between min and max)
  def finalDecision(self, gameState):

    #get the legal moves for Pacman
    legalMoves = gameState.getLegalActions(0)

    #define the v to be a large negative number since it is supposed to be negative infinity 
    v = -100000000

    #define alpha to be massively negative and beta to be massive initially
    alpha = -100000000
    beta = 100000000

    #set up a variable to hold the action from the max during the loop
    decisiveMove = "Directions.STOP"

    for move in legalMoves:
      #ignore stop direction
      if move != Directions.STOP:
        #get the successors for moves other than stop
        successorStates = gameState.generateSuccessor(0, move)
        #keep track of the previous v value for comparison
        oldV = v
        #get the max between the min of successor states and the current max
        v = max(v, self.minimumChoice(successorStates, 0, 1, alpha, beta))
        #if the current v is the new max, need to update the decision
        if oldV < v:
          decisiveMove = move
        #if the beta is less than the current, can just return v since it will be unchanged at this point
        if beta <= v:
          return decisiveMove
        #set the alpha to the max if it's bigger than the current alpha
        alpha = max(v, alpha)

    return decisiveMove

class ExpectimaxAgent(MultiAgentSearchAgent):
  """
    Your expectimax agent (question 4)
  """

  def getAction(self, gameState):
    """
      Returns the expectimax action using self.depth and self.evaluationFunction

      All ghosts should be modeled as choosing uniformly at random from their
      legal moves.
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
  """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
  """
  "*** YOUR CODE HERE ***"
  util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction

class ContestAgent(MultiAgentSearchAgent):
  """
    Your agent for the mini-contest
  """

  def getAction(self, gameState):
    """
      Returns an action.  You can use any method you want and search to any depth you want.
      Just remember that the mini-contest is timed, so you have to trade off speed and computation.

      Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
      just make a beeline straight towards Pacman (or away from him if they're scared!)
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

