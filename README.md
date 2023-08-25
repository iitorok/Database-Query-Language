# Database-Query-Language
Developed a database system that stores user input and reacts to commands given accordingly. For example, if the user types "CREATE <table name> <column number> <column type n>(types for however many columns specified) <column name n>, the program will create a new table with the information specified using an unordered map or a map depending on the usage. The unordered map acts as a hash table and the map acts as a binary search tree ADT.
The database takes in several commands:
CREATE: creates a new table. Example: CREATE emptytable 3 string double bool job salary need_car?
INSERT INTO: inserts data taking into account the column types previously created. Takes in a tablename and number of rows.
            Ex: INSERT INTO emptytab 2 ROWS
            doctor 100000 true
            lawyer 90000 true

PRINT FROM: takes in a table name, number of columns, and either a comparison or ALL. Ex: PRINT FROM emptytable 2 job salary ALL
            Ex2: PRINT FROM emptytable 2 job salary WHERE salary > 0
GENERATE FOR: creates an index of either type hash or bst on a table allowing a row in the table to be found rapidly given a particular value in the column <colname>.
              Ex: GENERATE FOR emptytab hash INDEX ON salary
              When generating a BST index, the program creates a binary search tree that allows rows in the table to be found rapidly given a particular value in the               column <colname>
              Ex2: GENERATE FOR emptytable bst INDEX ON job

DELETE FROM: takes in a table name and a comparison, then deletes all rows of data where comparison applies. Ex: DELETE FROM emptytable WHERE salary > 100000

JOIN: takes in two table names and prints columns where condition is met in both tables. Ex: JOIN emptytable AND fulltab WHERE need_car? = student? AND PRINT 3 job 1 pets 2 name 2.
    Note: the default format of JOIN is as follows: JOIN <tablename1> AND <tablename2> WHERE <colname1> = <colname2> AND PRINT <number of columns printed> <colname1> <tablenumber where column name is found> <columname2> <tablenumber where column name is found> (table number corresponds to the order in which the table numbers are inputted.)

REMOVE: deletes a table and its data entirely. Ex: REMOVE emptytable
QUIT: quits the program. Ex: QUIT
