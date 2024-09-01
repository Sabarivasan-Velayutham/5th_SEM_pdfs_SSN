

tree = {1:(2,3,4),2:(5,6,7),3:(8,9),4:(10,11),5:(12,13),6:(14,15),8:(16,17,18),10:(19,20,21),11:(22,23),14:(24,25),16:(26,27),18:(28,29),21:(30,31,32)}

values = [0,-1,-1,-1,-1,-1,-1,16,-1,12,-1,-1,4,13,-1,11,-1,9,-1,10,8,-1,7,4,5,10,1,8,6,12,2,5,7]

def minimax(position,depth,maximizingPlayer):

	if depth == 0 or position not in tree:
		return values[position]

	if maximizingPlayer:
		maxEval = -999
		for child in tree[position]:
			val = minimax(child,depth-1,False)
			maxEval = max(maxEval,val)
		values[position] =  maxEval
		return maxEval
		

	else:
		minEval = 999
		for child in tree[position]:
			val = minimax(child,depth-1,True)
			minEval = min(minEval,val)
		values[position] = minEval
		return minEval 

def alphabeta(position, depth, alpha, beta, maximizingPlayer):
	if depth == 0 or position not in tree:
		return values[position]
 
	if maximizingPlayer:
		maxEval = -999
		for child in tree[position]:
			val = alphabeta(child, depth - 1, alpha, beta, False)
			maxEval = max(maxEval, val)
			alpha = max(alpha, val)
			if beta <= alpha:
				break
		values[position] = maxEval
		return maxEval
 
	else:
		minEval = +999
		for child in tree[position]:
			val = alphabeta(child, depth - 1, alpha, beta, True)
			minEval = min(minEval, val)
			beta = min(beta, val)
			if beta <= alpha:
				break
		values[position] = minEval
		return minEval

print(minimax(1,4,True))
#print(alphabeta(1,4,-999,999,True))
print(values)



