import sqlite3
import os



if  not(os.path.isfile("cars.db")):
    db = sqlite3.connect("cars.db")
    cursor = db.cursor()
    name=input("please enter your name:")
    cursor.execute("CREATE TABLE car(id,name,price,seat,quantity)")
    cursor.execute("""
    INSERT INTO car VALUES
        (1,"ord Fiesta",120,4,8),
        (2,"Mazda2",100,4,10),
        (3,"Audi A4",200,4,3),
        (4,"Lexus LS",210,5,4),
        (5,"Cadillac CTS",260,4,3),
        (6,"Porsche 911",400,2,2),
        (7,"BMW Z4",300,2,5),
        (8,"Mazda CX-3",120,5,12),
        (9,"Hyundai Santa Fe",120,5,10),
        (10,"Toyota Camery",100,4,10)   
            """)
    cursor.execute("create table invoice(car_name,price)")
    cursor.execute("insert into invoice values(?,?)",(name,0))
    db.commit()
else:
    db = sqlite3.connect("cars.db")
    cursor = db.cursor()
    name=cursor.execute("select car_name from invoice where price=0")
    name=name.fetchone()[0]
class car ():
    def __init__(self,Name,Price,Quantity):
        self.__name=Name
        self.__price=Price
        self.__quantity=Quantity
    def increase_quantity(self):
        self.__quantity +=1
        cursor.execute("update car set quantity=? where name=?",(self.__quantity,self.__name))
    def decrease_quantity(self):
        self.__quantity -=1
        cursor.execute("update car set quantity=? where name=?",(self.__quantity,self.__name))
    def rent(self):
        car.decrease_quantity(self)
        cursor.execute("insert into invoice values (?,?)",(self.__name,self.__price//4))
        db.commit()
        os.system('cls')
        print("YOUR INVOICE".center(width))
        draw_line()
        show_invoice(self.__name,self.__price//4)
        ch=input("Enter any key to exit:")


def draw_line():
    for i in range(width):
        print("-",end='')
    print()


def car_list():
    datas=list(cursor.execute("select * from car"))
    os.system('cls')
    print("CAR LIST".center(width))
    draw_line()
    print(":   : {:30s}:   Price   :{:^20s}:{:^29s}:".format("Item Name","Seat","Quantity"))
    draw_line()
    for data in datas:
        print(":{:<3d}: {:30s}:{:^11d}:{:^20d}:{:^29d}:".format(data[0],data[1],data[2],data[3],data[4]))
        draw_line()
    ch=input("Select Car ID:")
    while(True): 
        if ch != '':
            try:
                ch=int(ch)           
                if datas[ch-1][4]!=0:
                    list_of_car[ch-1].rent()
                    break
                else:
                    ch=input("we don't have your selected car right now!\nplease  choose another car:")
            except:
                ch=input("invalid input!!enter Car ID for rent or ENTER for back to Menu!")
        else:
            return
        

def your_invoice():
    datas=list(cursor.execute("select * from invoice"))
    os.system('cls')
    print("YOUR INVOICE".center(width))
    draw_line()
    datas.remove((name,0))
    if datas==[]:
        print("You haven't rent any car yet!\n")
    else:
        for data in datas:
            show_invoice(data[0],data[1])
    ch=input("Enter any key to exit:")

def show_invoice(car_name,price):
    print("\t\t{:40s}{}".format("Name:",name))
    print("\t\t{:40s}{}".format("Car:",car_name))
    print("\t\t{:40s}{}".format("Numbers of days:",3))
    print("\t\t{:40s}{}".format("Day rent:",price))
    draw_line()

def Editing():
    os.system('cls')
    draw_line()
    print("1{:>70s}\n2{:>70s}".format("add a new car","change quantity of cars"))
    ch=int(input("YOUR CHOICE:"))
    if ch==1:
        id=list(cursor.execute("select id from car"))[-1][0]+1
        car_name=input("enter car name:")
        car_seat=int(input("enter car's seat:"))
        car_price=int(input("enter car's price:"))
        car_quantity=int(input("enter car's quantity:"))
        cursor.execute("insert into car values (?,?,?,?,?)",(id,car_name,car_price,car_seat,car_quantity))
        list_of_car.append(car(car_name,car_price,car_quantity))
    elif ch==2:
        datas=list(cursor.execute("select * from car"))
        os.system('cls')
        print("CAR LIST".center(width))
        draw_line()
        print(":   : {:30s}:   Price   :{:^20s}:{:^29s}:".format("Item Name","Seat","Quantity"))
        draw_line()
        for data in datas:
            print(":{:<3d}: {:30s}:{:^11d}:{:^20d}:{:^29d}:".format(data[0],data[1],data[2],data[3],data[4]))
            draw_line()
        ch=input("Select Car ID:")
        while(True): 
            ch2=input("1 to increase or 2 to decrease:")
            try:
                ch=int(ch)
                ch2=int(ch2)
                if ch2==1:     
                    list_of_car[ch-1].increase_quantity()
                    break
                elif ch2==2 and datas[ch-1][4]!=0:
                    list_of_car[ch-1].decrease_quantity()
                    break
                else:
                    ch=input("invalid input!!enter Car ID for edit:")
            except:
                ch=input("invalid input!!enter Car ID for edit:")
        

def delete():
    datas=list(cursor.execute("select * from car"))
    os.system('cls')
    print("CAR LIST".center(width))
    draw_line()
    print(":   : {:30s}:   Price   :{:^20s}:{:^29s}:".format("Item Name","Seat","Quantity"))
    draw_line()
    for data in datas:
        print(":{:<3d}: {:30s}:{:^11d}:{:^20d}:{:^29d}:".format(data[0],data[1],data[2],data[3],data[4]))
        draw_line()
    ch=input("Select the Car ID that you wanna delete or enter to back to home page:")
    while(True):
        if ch=='':
            break
        try:
            ch=int(ch)
            cursor.execute("delete from car where id=?",(ch,))            
            for index in range(ch+1,datas[-1][0]+1):
                cursor.execute("update car set id=? where id=?",(index-1,index,))
            list_of_car.__delitem__(ch)
            break
        except:
            ch=input("invalid input!!enter caar id:")

def Admin():
    os.system('cls')
    print("ADMIN".center(width))
    draw_line()
    pasw=input("please enter password to enter ADMIN panel:")
    #check the entered password!
    if pasw.encode().hex()==('6'+'16'+'46'+'d6'+'96'+'e616'+'46'+'d6'+'96e') or pasw.encode().hex()==('3'+'13'+'23'+'33'+'43'+'53'+'63'+'73'+'8'):
        os.system('cls')
        print("ADMIN".center(width))
        draw_line()
        print("Select your choice:\n1{:>70s}\n2{:>70s}\n3{:>70s}".format("Edit information","Delete information","Exit"))
        draw_line()
        while(True):
            ch=int(input("ENTER YOUR CHOICE:"))
            if ch==1:
                Editing()
                break
            elif ch==2:
                delete()
                break
            elif ch==3:
                break
            else:
                print("Invalid input!")
#seting important variable
Exit=False
width=100
data=cursor.execute("select name,price,quantity from car")
list_of_car=[]
for d in data:  
    list_of_car.append(car(d[0],d[1],d[2]))

while(not Exit):
    os.system('cls')
    print("MENU\n1 - Car List\n2 - check Your Invoice\n3 - Admin Panel\n4 - Exit")
    ch=input("YOUR CHOICE:")
    while(True):
        if ch=="1":
            car_list()
            break
        elif ch=="2":
            your_invoice()
            break
        elif ch=="3":
            Admin()
            break
        elif ch=="4":
            Exit=True
            break
        else:
            ch=input("invalid input!\nenter Your Choice:")

db.commit()
cursor.close()
