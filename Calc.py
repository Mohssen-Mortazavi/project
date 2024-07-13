operators = ["*","+","-"]


def find(exp,operator):
	end = len(exp)
	start = 0
	if(exp[0] == '-'):
		exp = exp[1:]	
		if operator in exp:
			index = list(exp).index(operator)
			for char in range(index+1,end-1):
				if exp[char] in operators:
					end = char -1
					
					break
			 
			for char in range(index-1,-1,-1):
				if exp[char] in operators:
					start = char +1
					break
			if(start != 0):
				start += 1
			end +=1
			exp = "-" + exp
			return start,end
		else:
			return -1,-1
	else:
		if operator in exp:
			index = list(exp).index(operator)
			for char in range(index+1,end):
				if exp[char] in operators:
					end = char-1
					break
			for char in range(index-1,-1,-1):
				if exp[char] in operators:
					start = char + 1
					break
			return start,end
		else:
			return -1,-1

def calculate(exp_with_one_operator):
	exp = list(exp_with_one_operator)
	brokenNumber =[0,0]
	if "*" in exp:
		index = exp.index('*')
	elif "+" in exp:
		index = exp.index('+')
	elif "-" in exp[1:]:
		index=exp[1:].index('-')+1
	if (exp[0] == '-'):
		exp_with_one_operator = exp_with_one_operator[1:]
		index -= 1
	brokenNumber = exp_with_one_operator.split(exp_with_one_operator[index])
	if(exp[0] == '-'):
		brokenNumber[0] = '-' + brokenNumber[0]
		index +=1
	if exp[index] == "*":
         return int(brokenNumber[0]) * int(brokenNumber[1])
	if exp[index] == "+":
         return int(brokenNumber[0]) + int(brokenNumber[1])
	if exp[index] == "-":
         return int(brokenNumber[0]) - int(brokenNumber[1])

def replace(exp,start,end,result):
         return exp.replace(exp[start:end+1],str(result))

def logic(exp):
	condition = True
	while condition:
		start,end = find(exp,"*")
		if start == -1:
			break
		result = calculate(exp[start:end+1])
		exp = replace(exp,start,end,result)
	condition = True
	while condition:
		
		startForPlus,endForPlus = find(exp,"+")
		startForMinus,endForMinus = find(exp,"-")
		if startForPlus != -1 and startForMinus != -1:
			if startForPlus < startForMinus:
				result = calculate(exp[startForPlus:endForPlus+1])
				exp = replace(exp,startForPlus,endForPlus,result)
			else:
				result = calculate(exp[startForMinus:endForMinus+1])
				exp = replace(exp,startForMinus,endForMinus,result)   
		elif startForPlus != -1:
			result = calculate(exp[startForPlus:endForPlus+1])
			exp = replace(exp,startForPlus,endForPlus,result)
		elif startForMinus != -1:
			result = calculate(exp[startForMinus:endForMinus+1])
			
			exp = replace(exp,startForMinus,endForMinus,result)         

		else:
			 condition = False
	return exp          

loop = True
while loop == True:
	exp = input("enter a mathematical expression that have + - * / :")
	print(logic(exp))
	loop= True if input("do you wanna continue ( y or n ):")=='y'else False

