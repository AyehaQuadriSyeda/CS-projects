#
#  Author: Ayesha Quadri Syeda
#  Due Date: 9/16/2022
#  Purpose: Output data from the CTA2_L_daily_ridership database 
#  according to the users commands
#

import sqlite3
import matplotlib.pyplot as plt


##################################################################  
#
# print_stats
#
# Given a connection to the CTA database, executes various
# SQL queries to retrieve and output basic stats.
#
def print_stats(dbConn):
    dbCursor = dbConn.cursor()
    
    print("General stats:")

    #  number of stations
    dbCursor.execute("Select count(*) From Stations;")
    row = dbCursor.fetchone();
    print("  # of stations:", f"{row[0]:,}")

    #  number of stops
    dbCursor.execute("Select count(*) From Stops;")
    row = dbCursor.fetchone();
    print("  # of stops:", f"{row[0]:,}")

    #  number of ride enteries
    dbCursor.execute("Select count(*) From Ridership;")
    row = dbCursor.fetchone();
    print("  # of ride entries:", f"{row[0]:,}")

    #  date range
    sql = """Select MIN(strftime('%Y-%m-%d', Ride_Date)),
             MAX(strftime('%Y-%m-%d', Ride_Date))
             From Ridership;"""
    dbCursor.execute(sql)
    row = dbCursor.fetchone();
    print("  date range:", f"{row[0]:}", "-" ,f"{row[1]:}")

    #Total Ridership
    dbCursor.execute("Select sum(Num_Riders) From Ridership;")
    row = dbCursor.fetchone();
    print("  Total ridership:", f"{row[0]:,}")
    total = row[0]

    #  weekday Ridership
    sql = """Select sum(Num_Riders) From Ridership 
          where Type_of_Day = 'W';"""
    dbCursor.execute(sql)
    row = dbCursor.fetchone();
    percentage = round((row[0]/total) * 100, 2)
    print("  Weekday ridership:", f"{row[0]:,}", "({}%)".format(percentage))

    #  Saturday ridership
    sql = """Select sum(Num_Riders) From Ridership 
          where Type_of_Day = 'A';"""
    dbCursor.execute(sql)
    row = dbCursor.fetchone();
    percentage = round((row[0]/total) * 100, 2)
    print("  Saturday ridership:", f"{row[0]:,}", 
          "({}%)".format(percentage))

    #  Sunday/Holiday ridership
    sql = """Select sum(Num_Riders) From Ridership 
          where Type_of_Day = 'U';"""
    dbCursor.execute(sql)
    row = dbCursor.fetchone();
    percentage = round((row[0]/total) * 100, 2)
    print("  Sunday/holiday ridership:", f"{row[0]:,}", 
          "({}%)".format(percentage))
     
###############################################################
#
#  command 1
#  Given a database, asks for a partial station name
#  then lists all the stations that include the partial name
#  in ascending order

def command_one(dbConn):
  dbCursor = dbConn.cursor()

  print()
  name = input('Enter partial station name (wildcards _ and %): ')
  sql = """Select Station_ID, Station_Name
           From Stations
           where Station_Name like ?
           order by Station_Name asc;"""
  dbCursor.execute(sql, [name])
  rows = dbCursor.fetchall();
  if len(rows) == 0:
    print('**No stations found...')
    print()
  else:
    for row in rows:
      print(f"{row[0]:}", ":", row[1])
    print()

###############################################################
#
#  command 2
#  Outputs the ridership at each station 
#  and the percentage of usage from the entire ridership
#
#
def command_two(dbConn):
  dbCursor = dbConn.cursor()

  print('** ridership all stations **')
  sql = """Select Stations.Station_Name, sum(Num_Riders)
           From Ridership
           join Stations
           on Ridership.Station_ID = Stations.Station_ID
           group by Ridership.Station_ID
           order by Stations.Station_Name asc;"""
  dbCursor.execute(sql)

  rows = dbCursor.fetchall()

  dbCursor.execute("Select sum(Num_Riders) From Ridership;")
  row = dbCursor.fetchone();
  total = row[0]

  for row in rows:
    print(row[0], ":", f"{row[1]:,}", 
          f"({(row[1]/total)*100:.2f}%)")

###############################################################
#
#  command 3
#  outputs the top 10 busiest stations 
#
#
def command_three(dbConn):
  dbCursor = dbConn.cursor()

  print('** top-10 stations **')
  sql = """Select Stations.Station_Name, sum(Num_Riders) as num
           From Ridership
           join Stations
           on Ridership.Station_ID = Stations.Station_ID
           group by Ridership.Station_ID
           order by num desc
           limit 10;"""
  dbCursor.execute(sql)

  rows = dbCursor.fetchall()

  ## find total ridership
  dbCursor.execute("Select sum(Num_Riders) From Ridership;")
  row = dbCursor.fetchone();
  total = row[0]

  for row in rows:
    print(row[0], ":", f"{row[1]:,}", 
          f"({(row[1]/total)*100:.2f}%)")
  print()

###############################################################
#
#  command 4
#  outputs the top 10 least busiest stations 
#
#
def command_four(dbConn):
  dbCursor = dbConn.cursor()

  print()
  print('** least-10 stations **')
  sql = """Select Stations.Station_Name, sum(Num_Riders) as num
           From Ridership
           join Stations
           on Ridership.Station_ID = Stations.Station_ID
           group by Ridership.Station_ID
           order by num asc
           limit 10;"""
  dbCursor.execute(sql)

  rows = dbCursor.fetchall()

  dbCursor.execute("Select sum(Num_Riders) From Ridership;")
  row = dbCursor.fetchone();
  total = row[0]

  for row in rows:
    print(row[0], ":", f"{row[1]:,}", 
          f"({(row[1]/total)*100:.2f}%)")
  print()
###############################################################
#
#  command 5
#  outputs the top 10 least busiest stations 
#
#
def command_five(dbConn):
  dbCursor = dbConn.cursor()

  color = input('Enter a line color (e.g. Red or Yellow):')

  sql = """Select Stops.Stop_Name, Stops.Direction, Stops.ADA
           From Lines
           join StopDetails
           on Lines.Line_ID = StopDetails.Line_ID
           join Stops
           on StopDetails.Stop_ID = Stops.Stop_ID
           where Lines.Color like ?"""
  dbCursor.execute(sql, [color])

  rows = dbCursor.fetchall()

  if len(rows) != 0:
    for row in rows:
      if(row[2] == 1):
        print(row[0], ": direction = ", f"{row[1]:}", "(accessible = Yes)")
      if(row[2] == 0):
        print(row[0], ": direction = ", f"{row[1]:}",
              "(accessible = No)")
  else:
    print('**No such line...')
  
  print()
###############################################################
#
#  command 6
#  outputs the total ridership by month and 
#  gives the option to plot the data
#
#
def command_six(dbConn):
  dbCursor = dbConn.cursor()

  sql = """Select strftime('%m', Ride_Date) as month,
           sum(Num_Riders)
           From Ridership
           group by month
           order by month asc;"""

  dbCursor.execute(sql)

  rows = dbCursor.fetchall()

  print('** ridership by month **')
  for row in rows:
    print(row[0], ':', f"{row[1]:,}")
  print()

  ans = input('Plot? (y/n) ')
  if ans == 'y':
    x = []
    y = []

    for row in rows:
      x.append(row[0])
      y.append(row[1])

    plt.xlabel("month")
    plt.ylabel("number of riders (x*10^8)")
    plt.title("monthly ridership")

    plt.plot(x, y)
    plt.show()
    print()
###############################################################
#
#  command 7
#  outputs the total ridership by year and 
#  gives the option to plot the data
#
#
def command_seven(dbConn):
  dbCursor = dbConn.cursor()

  ## Get Data
  sql = """Select strftime('%Y', Ride_Date) as year,
           sum(Num_Riders)
           From Ridership
           group by year
           order by year asc;"""

  dbCursor.execute(sql)

  rows = dbCursor.fetchall()

  print('** ridership by year **')
  for row in rows:
    print(row[0], ':', f"{row[1]:,}")
  print()

  ##  prompt and plot
  ans = input('Plot? (y/n) ')
  if ans == 'y':
    x = []
    y = []

    for row in rows:
      x.append(row[0][2:4])
      y.append(row[1])

    plt.xlabel("year")
    plt.ylabel("number of riders (x*10^8)")
    plt.title("yearly ridership")

    plt.plot(x, y)
    plt.show()

##################################################################  
#
#  Queries the data for Station 1 in Command 8
#
def eight_Station1(s1, x1, y1, rows):

  print('Station 1:', rows[0][1], rows[0][0])
  count = 0
  for row in rows:
    if count > 4 and count < (len(rows) - 5):
      x1.append(count)
      y1.append(row[3])
      count += 1
      continue
    else:
      x1.append(count)
      y1.append(row[3])
      print(row[2], row[3])
      count += 1

##################################################################  
#
#  Queries the data for Station 2 in Command 8
#
def eight_Station2(s2, x2, y2, rows):
  print('Station 2:', rows[0][1], rows[0][0])
  
  count = 0
  for row in rows:
    if count > 4 and count < (len(rows) - 5):
      x2.append(count)
      y2.append(row[3])
      count += 1
      continue
    else:
      x2.append(count)
      y2.append(row[3])
      print(row[2], row[3])
      count += 1

##################################################################  
#
# Plot the data for command 8
#
def eight_Plot(year, x1, y1, x2, y2, station1, station2):
  plt.xlabel("day")
  plt.ylabel("number of riders")
  plt.title("riders each day of {}".format(year))
  plt.plot(x1, y1)
  plt.plot(x2, y2)
  plt.legend([station1, station2])
  plt.show()

##################################################################  
#
#  Queries, asks for user input and checks 
#  wheather the input is acceptable
#
def eight_check(dbConn):
  dbCursor = dbConn.cursor()

  print()
  year = input('Year to compare against? ')

  ## Check Station Name 1
  print()
  s1 = input('Enter station 1 (wildcards _ and %): ')
  
  sql = """Select Station_Name
           from Stations
           where Station_Name like ?;"""
  dbCursor.execute(sql, [s1])
  rows1 = dbCursor.fetchall()
  if len(rows1) > 1:
    print('**Multiple stations found...')
    print()
    return
  if len(rows1) == 0:
    print('**No station found...')
    print()
    return

  ## Check Station Name 2
  print()
  s2 = input('Enter station 2 (wildcards _ and %): ')
  dbCursor.execute(sql, [s2])
  rows2 = dbCursor.fetchall()
  if len(rows2) > 1:
    print('**Multiple stations found...')
    print()
    return
  if len(rows2) == 0:
    print('**No station found...')
    print()
    return
    
  command_eight(dbCursor, year, s1, s2)

##################################################################  
#
#  Command 8
#  compares Two user given stations at a certain year by 
#  ridership
#
def command_eight(dbCursor, year, s1, s2):

  sql = """Select Stations.Station_Name, Stations.Station_ID,
           strftime('%Y-%m-%d', Ride_Date) as date, 
           Num_Riders
           from Ridership
           join Stations
           on Ridership.Station_ID = Stations.Station_ID
           where strftime('%Y', Ride_Date) = ?
           and Stations.Station_Name like ?
           order by date asc;"""

  x1 = []
  y1 = []
  
  ##  Station 1 data
  dbCursor.execute(sql, [year, s1])
  rows1 = dbCursor.fetchall()
  station1 = rows1[0][0]
  eight_Station1(s1, x1, y1, rows1)

  x2 = []
  y2 = []

  ##   Station 2 data
  dbCursor.execute(sql, [year, s2])
  
  rows2 = dbCursor.fetchall()
  station2 = rows2[0][0]
  eight_Station2(s2, x2, y2, rows2)

  ## plot
  ans = input("Plot? (y/n) ")
  if ans == 'y':
    eight_Plot(year, x1, y1, x2, y2, station1, station2)
  print()

##################################################################  
#
#  Command 9
#  Finds all the stations that run on a certain colored line
#  and allows the user to plot the data on a map
#
def command_nine(dbConn):
  dbCursor = dbConn.cursor()

  print()
  color = input("Enter a line color (e.g. Red or Yellow): ")
  sql = """Select distinct Stations.Station_Name, Stops.Latitude,
           Stops.Longitude
           from Lines
           join StopDetails
           on Lines.Line_ID = StopDetails.Line_ID
           join Stops
           on StopDetails.Stop_ID = Stops.Stop_ID
           join Stations
           on Stops.Station_ID = Stations.Station_ID
           where Lines.Color like ?
           order by Stations.Station_Name asc;"""

  x = []
  y = []
  
  dbCursor.execute(sql, [color])
  rows = dbCursor.fetchall()

  if len(rows) == 0:
    print('**No such line...')
    return
  else:
    for row in rows:
      x.append(row[2])
      y.append(row[1])
      print(row[0], ":", f"({row[1]:},", f"{row[2]:,})")
    print()

  ## plot
  ans = input("Plot? (y/n) ")
  if ans == 'y':
    image = plt.imread("chicago.png")
    xydims = [-87.9277, -87.5569, 41.7012, 42.0868]
    plt.imshow(image, extent=xydims)
    if color.lower() == 'purple-express':
      color = Purple
    plt.title(color.lower() + " line")
    plt.plot(x, y, "o", c=color)
    for row in rows:
      plt.annotate(row[0], (row[2], row[1]))
    plt.xlim([-87.9277, -87.5569])
    plt.ylim([41.7012, 42.0868])
    plt.show()
  print()
  
##################################################################  
#
# main
#
print('** Welcome to CTA L analysis app **')
print()

dbConn = sqlite3.connect('CTA2_L_daily_ridership.db')

print_stats(dbConn)
print()

val = input('Please enter a command (1-9, x to exit): ')

while val != 'x':
  if val == '1':
    command_one(dbConn)
  elif val == '2':
    command_two(dbConn)
  elif val == '3':
    command_three(dbConn)
  elif val == '4':
    command_four(dbConn)
  elif val == '5':
    command_five(dbConn)
  elif val == '6':
    command_six(dbConn)
  elif val == '7':
    command_seven(dbConn)
  elif val == '8':
    eight_check(dbConn)
  elif val == '9':
    command_nine(dbConn)
  else:
    print('**Error, unknown command, try again...')
    print()
    
  val = input('Please enter a command (1-9, x to exit): ')
#
# done
#