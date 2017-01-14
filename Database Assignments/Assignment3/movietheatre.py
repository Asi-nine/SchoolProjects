#Author Peter Valovcik
#Assignment for Databases
#Website to access a movie theatre database

from flask import Flask, render_template, request, session
import mysql.connector

app = Flask(__name__)

#need this to use session
app.secret_key = 'THISISAREALLYBADCHOICEASASECRETKEY'

#the homepage
@app.route("/")
def hello():
    return render_template('start.html')

#staff page
@app.route('/staff')
def staff():
    return render_template('staff.html')

#staff movie page
@app.route('/staff_movies')
def staff_movies():
    return render_template('staff_movies.html')

#page to add a movie for staff
@app.route('/movies_add')
def movies_add():
    return render_template('movies_add.html')

#when submit to add a movie is clicked, this executes and adds it to the db
@app.route('/movies_add_submit', methods=["POST"])
def movies_add_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    #hack to get a unique ID
    query = ("SELECT idMovie from Movie")
    cursor.execute(query)
    oldids=cursor.fetchall()
    newid = max(oldids)[0]
    newid = newid+1

    insert_stmt = (
        "INSERT INTO Movie (idMovie, MovieName, MovieYear) VALUES (%s, %s, %s)"
    )
    data = (newid, request.form['moviename'], request.form['movieyear'])
    cursor.execute(insert_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('movies_add.html')

#page to remove a movie for staff
@app.route('/movies_remove')
def movies_remove():
    return render_template('movies_remove.html')

#when submit to remove a movie is clicked, this executes and removes it from the db
@app.route('/movies_remove_submit', methods=["POST"])
def movies_remove_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    remove_stmt = (
        "DELETE FROM Movie WHERE idMovie = %(idMovie)s"
    )
    data = request.form['movieid']
    cursor.execute(remove_stmt, {'idMovie': data})
    cnx.commit()
    cnx.close()
    return render_template('movies_remove.html')

#page to modify movies for staff
@app.route('/movies_mod')
def movies_mod():
    return render_template('movies_mod.html')

#when submit to modify a movie is clicked, this executes and modifies it on the db
@app.route('/movies_mod_submit', methods=["POST"])
def movies_mod_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    update_stmt = (
        "UPDATE Movie SET MovieName = %s, MovieYear = %s WHERE idMovie = %s"
    )
    data = request.form['moviename'], request.form['movieyear'], request.form['movieid']
    cursor.execute(update_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('movies_mod.html')

#staff page that lists all movies in the db listed alphabetically by name
@app.route('/movies_list')
def movies_list():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT MovieName, idMovie, MovieYear from Movie order by MovieName")
    cursor.execute(query)
    movies=cursor.fetchall()
    cnx.close()
    return render_template('movies_list.html', movies=movies)

#default page for genres for staff
@app.route('/staff_genres')
def staff_genres():
    return render_template('staff_genres.html')

#page to add a genre for staff
@app.route('/genres_add')
def genres_add():
    return render_template('genres_add.html')

#when submit to add a genre is clicked, this executes and adds it to the db
@app.route('/genres_add_submit', methods=["POST"])
def genres_add_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    insert_stmt = (
        "INSERT INTO Genre (Movie_idMovie, Genre) VALUES (%s, %s)"
    )
    data = request.form['movieid'], request.form['genrename']
    cursor.execute(insert_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('genres_add.html')

#page to remove a genre for staff
@app.route('/genres_remove')
def genres_remove():
    return render_template('genres_remove.html')

#when submit to remove a genre is clicked, this executes and removes it from the db
@app.route('/genres_remove_submit', methods=["POST"])
def genres_remove_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    remove_stmt = (
        "DELETE FROM Genre WHERE Movie_idMovie = %s AND Genre = %s"
    )
    data = request.form['movieid'], request.form['genrename']
    cursor.execute(remove_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('genres_remove.html')

#page for staff to list all genres alphabetically by genre, and also their corresponding movies
@app.route('/genres_list')
def genres_list():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT Genre, MovieName FROM Movie, Genre Where Genre.Movie_idMovie = idMovie ORDER BY Genre")
    cursor.execute(query)
    genres=cursor.fetchall()
    cnx.close()
    return render_template('genres_list.html', genres=genres)

#default page for rooms for staff
@app.route('/staff_rooms')
def staff_rooms():
    return render_template('staff_rooms.html')

#page to add a room for staff
@app.route('/rooms_add')
def rooms_add():
    return render_template('rooms_add.html')

#when submit to add a room is clicked, this executes and adds it to the db
@app.route('/rooms_add_submit', methods=["POST"])
def rooms_add_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    #hack to get a unique ID
    query = ("SELECT RoomNumber from TheatreRoom")
    cursor.execute(query)
    oldids=cursor.fetchall()
    newid = max(oldids)[0]
    newid = newid+1

    insert_stmt = (
        "INSERT INTO TheatreRoom (RoomNumber, Capacity) VALUES (%s, %s)"
    )
    data = newid, request.form['capacity']
    cursor.execute(insert_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('rooms_add.html')

#page to remove a room for staff
@app.route('/rooms_remove')
def rooms_remove():
    return render_template('rooms_remove.html')

#when submit to remove a room is clicked, this executes and reomves it from the db
@app.route('/rooms_remove_submit', methods=["POST"])
def rooms_remove_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    remove_stmt = (
        "DELETE FROM TheatreRoom WHERE RoomNumber = %(RoomNumber)s"
    )
    data = request.form['roomnumber']
    cursor.execute(remove_stmt, {'RoomNumber': data})
    cnx.commit()
    cnx.close()
    return render_template('rooms_remove.html')

#page for staff to modify rooms
@app.route('/rooms_mod')
def rooms_mod():
    return render_template('rooms_mod.html')

#when submit to modify a room is clicked, this executes and modifies it on the db
@app.route('/rooms_mod_submit', methods=["POST"])
def rooms_mod_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    update_stmt = (
        "UPDATE TheatreRoom SET Capacity = %s WHERE RoomNumber = %s"
    )
    data = request.form['capacity'], request.form['roomnumber']
    cursor.execute(update_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('rooms_mod.html')

#page for staff to list all rooms sorted by room number
@app.route('/rooms_list')
def rooms_list():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT RoomNumber, Capacity from TheatreRoom order by RoomNumber")
    cursor.execute(query)
    rooms=cursor.fetchall()
    cnx.close()
    return render_template('rooms_list.html', rooms=rooms)

#default page for showings for staff
@app.route('/staff_showings')
def staff_showings():
    return render_template('staff_showings.html')

#page for staff to add a showing
@app.route('/showings_add')
def showings_add():
    return render_template('showings_add.html')

#when submit to add a showing is clicked, this executes and adds it to the db
@app.route('/showings_add_submit', methods=["POST"])
def showings_add_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    #hack to get a unique ID
    query = ("SELECT idShowing from Showing")
    cursor.execute(query)
    oldids=cursor.fetchall()
    newid = max(oldids)[0]
    newid = newid+1

    insert_stmt = (
        "INSERT INTO Showing (idShowing, ShowingDateTime, Movie_idMovie, TheatreRoom_RoomNumber, TicketPrice) VALUES (%s, %s, %s, %s, %s)"
    )
    data = newid, request.form['datetime'], request.form['movieid'], request.form['roomnumber'], request.form['price']
    cursor.execute(insert_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('showings_add.html')

#page to remove a showing for staff
@app.route('/showings_remove')
def showings_remove():
    return render_template('showings_remove.html')

#when submit to remove a showing is clicked, this executes and removes it from the db
@app.route('/showings_remove_submit', methods=["POST"])
def showings_remove_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    remove_stmt = (
        "DELETE FROM Showing WHERE idShowing = %(idShowing)s"
    )
    data = request.form['showingid']
    cursor.execute(remove_stmt, {'idShowing': data})
    cnx.commit()
    cnx.close()
    return render_template('showings_remove.html')

#page to modify a showing for staff
@app.route('/showings_mod')
def showings_mod():
    return render_template('showings_mod.html')

#when submit to modify a showing is clicked, this executes and modifies it on the db
@app.route('/showings_mod_submit', methods=["POST"])
def showings_mod_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    update_stmt = (
        "UPDATE Showing SET ShowingDateTime = %s, Movie_idMovie = %s, TheatreRoom_RoomNumber = %s, TicketPrice = %s WHERE idShowing = %s"
    )
    data = request.form['datetime'], request.form['movieid'], request.form['roomnumber'], request.form['price'], request.form['showingid']
    cursor.execute(update_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('showings_mod.html')

#page for staff to list all showings sorted by the date of the showing
@app.route('/showings_list')
def showings_list():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT ShowingDateTime, idShowing, Movie_idMovie, TheatreRoom_RoomNumber, TicketPrice from Showing order by ShowingDateTime")
    cursor.execute(query)
    showings=cursor.fetchall()
    cnx.close()
    return render_template('showings_list.html', showings=showings)

#defualt customer page for staff
@app.route('/staff_customers')
def staff_customers():
    return render_template('staff_customers.html')

#page to add a customer for staff
@app.route('/customers_add')
def customers_add():
    return render_template('customers_add.html')

#when submit to add a customer is clicked, this executes and adds it to the db
@app.route('/customers_add_submit', methods=["POST"])
def customers_add_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    #hack to get a unique ID
    query = ("SELECT idCustomer from Customer")
    cursor.execute(query)
    oldids=cursor.fetchall()
    newid = max(oldids)[0]
    newid = newid+1

    insert_stmt = (
        "INSERT INTO Customer (idCustomer, FirstName, LastName, EmailAddress, Sex) VALUES (%s, %s, %s, %s, %s)"
    )
    data = newid, request.form['firstname'], request.form['lastname'], request.form['email'], request.form['sex']
    cursor.execute(insert_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('customers_add.html')

#page to remove a customer for staff
@app.route('/customers_remove')
def customers_remove():
    return render_template('customers_remove.html')

#when submit to remove a customer is clicked, this executes and removes it the db
@app.route('/customers_remove_submit', methods=["POST"])
def customers_remove_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    remove_stmt = (
        "DELETE FROM Customer WHERE idCustomer = %(idCustomer)s"
    )
    data = request.form['customerid']
    cursor.execute(remove_stmt, {'idCustomer': data})
    cnx.commit()
    cnx.close()
    return render_template('customers_remove.html')

#page to modify a customer for staff
@app.route('/customers_mod')
def customers_mod():
    return render_template('customers_mod.html')

#when submit to modify a customer is clicked, this executes and modifies it on the db
@app.route('/customers_mod_submit', methods=["POST"])
def customers_mod_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    update_stmt = (
        "UPDATE Customer SET FirstName = %s, LastName = %s, EmailAddress = %s, Sex = %s WHERE idCustomer = %s"
    )
    data = request.form['firstname'], request.form['lastname'], request.form['email'], request.form['sex'], request.form['customerid']
    cursor.execute(update_stmt, data)
    cnx.commit()
    cnx.close()
    return render_template('customers_mod.html')

#page for staff to list all customers sorted by last name
@app.route('/customers_list')
def customers_list():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT LastName, FirstName, Sex, EmailAddress, idCustomer from Customer order by LastName")
    cursor.execute(query)
    customers=cursor.fetchall()
    cnx.close()
    return render_template('customers_list.html', customers=customers)


#page for staff to list all paid attendances, their attributes, cutomer names, showing ID and date/time, movie id and title, sorted by rating 
@app.route('/staff_attend')
def staff_attend():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT Rating, Customer_idCustomer, Customer.FirstName, Customer.LastName,"
        " Showing_idShowing, Showing.ShowingDateTime, Showing.Movie_idMovie, Movie.MovieName FROM Attend,"
        " Customer, Showing, Movie WHERE Customer_idCustomer = Customer.idCustomer"
        " AND Showing_idShowing = Showing.idShowing AND Showing.Movie_idMovie = idMovie order by Rating")
    cursor.execute(query)
    attends=cursor.fetchall()
    cnx.close()
    return render_template('staff_attend.html', attends=attends)

#first page for cutomers where they must select their name and email. These MUST match, and are saved in order to use the customer ID later
@app.route('/customer_select')
def customer_select():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT DISTINCT FirstName from Customer order by FirstName")
    cursor.execute(query)
    customersf=cursor.fetchall()
    query = ("SELECT DISTINCT LastName from Customer order by LastName")
    cursor.execute(query)
    customersl=cursor.fetchall()
    query = ("SELECT EmailAddress from Customer")
    cursor.execute(query)
    customerse=cursor.fetchall()
    cnx.close()
    return render_template('customer_select.html', customerse=customerse, customersl=customersl, customersf=customersf)

#default page for a customer. Redirects to a missing page if there is and email and name mismatch.
@app.route('/customer_submit', methods=["POST"])
def customer_submit():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT idCustomer from Customer WHERE FirstName = %s AND LastName = %s")
    data = request.form['fname'], request.form['lname']
    cursor.execute(query, data)
    cusid=cursor.fetchall()
    if not cusid:
        return render_template('customer_missing.html')
    testid = cusid[0][0]
    query = ("SELECT idCustomer from Customer WHERE EmailAddress = %(eadd)s")
    data = request.form['email']
    cursor.execute(query, {'eadd': data})
    cusid=cursor.fetchall()
    session['storedID'] = cusid[0][0]
    if(session['storedID'] != testid):
        return render_template('customer_missing.html')
    return render_template('customer.html', fname=request.form['fname'], lname=request.form['lname'] )

#page where a customer is shown all shows they have been to and can rate them
@app.route('/rate_showings')
def rate_showings():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT DISTINCT Showing_idShowing, Rating, Movie.MovieName, Showing.ShowingDateTime"
        " FROM Attend, Customer, Showing, Movie WHERE Customer_idCustomer = %s"
        " AND Showing_idShowing = Showing.idShowing AND Showing.Movie_idMovie = idMovie order by Showing_idShowing"
        )
    data =(session['storedID'],)
    cursor.execute(query, data)
    attends=cursor.fetchall()
    cnx.close()
    return render_template('rate_showings.html', attends=attends)

#upon choosing to rate a show the DB updates the rating
@app.route('/update_ratings', methods=["POST"])
def update_ratings():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    update_stmt = (
        "UPDATE Attend SET Rating = %s WHERE Customer_idCustomer = %s AND Showing_idShowing = %s"
    )
    data = request.form['newrating'], session['storedID'], request.form['showid']
    cursor.execute(update_stmt, data)
    cnx.commit()
    query = ("SELECT DISTINCT Showing_idShowing, Rating, Movie.MovieName, Showing.ShowingDateTime"
        " FROM Attend, Customer, Showing, Movie WHERE Customer_idCustomer = %s"
        " AND Showing_idShowing = Showing.idShowing AND Showing.Movie_idMovie = idMovie order by Showing_idShowing"
        )
    data = (session['storedID'],)
    cursor.execute(query, data)
    attends=cursor.fetchall()
    cnx.close()
    return render_template('rate_showings.html', attends=attends)

#page that allows the customer to search showings based on genre, date/time, name, and whether it is sold out
@app.route('/search_showings')
def search_showings():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT DISTINCT Genre FROM Genre order by Genre")
    cursor.execute(query)
    genres=cursor.fetchall()
    query = ("SELECT DISTINCT ShowingDateTime FROM Showing order by ShowingDateTime")
    cursor.execute(query)
    dates=cursor.fetchall()
    cnx.close()
    return render_template('search_showings.html', genres=genres, dates=dates)

#executes the customer search and returns the results. Allows the customer to purchase tickets to a show based on results.
@app.route('/searched_showings', methods=["POST"])
def searched_showings():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    if (not request.form.get('notfull')):
        query = ("SELECT idShowing, MovieName, Genre, ShowingDateTime, TicketPrice FROM Showing, Movie, Genre WHERE Genre.Genre = %s "
        " AND Showing.ShowingDateTime >= %s AND Showing.ShowingDateTime <= %s AND Movie.MovieName LIKE %s"
        " AND Showing.Movie_idMovie = Movie.idMovie AND Movie.idMovie = Genre.Movie_idMovie"
        )
    else:
        query = ("SELECT idShowing, MovieName, Genre, ShowingDateTime, TicketPrice FROM Showing, Movie, Genre"
        " WHERE Genre.Genre = %s AND Showing.ShowingDateTime >= %s AND Showing.ShowingDateTime <= %s AND Movie.MovieName LIKE %s"
        " AND Showing.Movie_idMovie = Movie.idMovie  AND Movie.idMovie = Genre.Movie_idMovie"
        " AND Showing.idShowing NOT IN (SELECT idShowing FROM Showing, TheatreRoom, Attend WHERE Attend.Showing_idShowing ="
        " Showing.idShowing AND Showing.TheatreRoom_RoomNumber = TheatreRoom.RoomNumber AND TheatreRoom.Capacity >"
        " (SELECT COUNT(Attend.Customer_idCustomer) FROM Attend))"
        )

    data = (request.form['chosengenre'], request.form['startdate'], request.form['enddate'], ("%" + request.form['moviename'] + "%"))
    cursor.execute(query, data)
    stuff=cursor.fetchall()

    return render_template('searched_showings.html', stuff=stuff)

#confirmation page for a ticket purchase which also adds that showing to the attend table.
@app.route('/ticket_purchased', methods=["POST"])
def ticket_purchased():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()

    insert_stmt = (
        "INSERT INTO Attend (Customer_idCustomer, Showing_idShowing) VALUES (%s, %s)"
    )
    data = session['storedID'], request.form['chosenshowing']
    cursor.execute(insert_stmt, data)
    cnx.commit()
    cnx.close()    
    return render_template('ticket_purchased.html')

#a profile of some info on the customer from the DB, including name, email, sex, id, total spent, and total movies seen
@app.route('/customer_profile')
def customer_profile():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()
    query = ("SELECT * FROM Customer WHERE Customer.idCustomer = %s")
    data = (session['storedID'],)
    cursor.execute(query, data)
    customer=cursor.fetchall()
    query = ("SELECT SUM(TicketPrice) FROM Customer, Attend, Showing WHERE Customer.idCustomer = %s AND Attend.Customer_idCustomer ="
        " %s AND Attend.Showing_idShowing = Showing.idShowing")
    data = session['storedID'], session['storedID']
    cursor.execute(query, data)
    total=cursor.fetchall()
    query = ("SELECT COUNT(Showing_idShowing) FROM Attend, Customer WHERE idCustomer = %s AND Attend.Customer_idCustomer = %s")
    data = session['storedID'], session['storedID']
    cursor.execute(query, data)
    movies=cursor.fetchall()
    return render_template('customer_profile.html', customer=customer, total=total, movies=movies)

#default sql injection test page, allowing search of a movie
@app.route('/sql_injection')
def sql_injection(name=None):
    return render_template('sql_injection.html')

#executes a movie search while allowing for sql injection
@app.route('/sql_injection_results', methods=["POST"])
def sql_injection_results():
    cnx = mysql.connector.connect(user='root', database='MovieTheatre')
    cursor = cnx.cursor()

    movieName = request.form['moviename']
    query = ("SELECT * from Movie where MovieName = '" + movieName + "'")
    cursor.execute(query)
    queryPassed= query
    movies=cursor.fetchall()
    cnx.commit()
    cnx.close()
    return render_template('sql_injection_results.html', movies=movies, queryPassed=queryPassed)

#change the IP here if you need to!!
if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
