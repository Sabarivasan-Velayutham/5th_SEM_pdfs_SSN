def create(r,c):
    m = [[0]*c]*r
    for i in range(r):
        for j in range(c):
            m[i][j] = float(input(f"{i,j} Value : "))

    return m[r-1][c-1]

def main():
    nv = int(input("Enter the number of variables : "))
    t = ''
    s = 1
    for i in range(nv):
        t = input("Enter the variable : ")
        print("Matrix for ", t)
        r = int(input("Enter the row : "))
        c = int(input("Enter the column : "))
        s *= create(r,c)

    print("Value for BBN is ",s)
    
main()