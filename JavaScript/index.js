const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const mysql = require('mysql');

const cors = require('cors');

const {MongoClient, ObjectId, ServerApiVersion} = require("mongodb");

/*------------------------------------------
--------------------------------------------
parse application/json
--------------------------------------------
--------------------------------------------*/
app.use(bodyParser.json());

app.use(cors({origin: '*'}));
/*------------------------------------------
--------------------------------------------
Database Connection
--------------------------------------------
--------------------------------------------*/
const conn = mysql.createConnection({
  // host: '104.154.29.133',
  host: process.env['ip_address'],
  user: process.env['user'], /* MySQL User */
  password: process.env['password'], /* MySQL Password */
  database: process.env['database'] /* MySQL Database */
});


/*------------------------------------------
--------------------------------------------
MongoDB Client Connect
--------------------------------------------
--------------------------------------------*/
const uri = "mongodb+srv://myAtlasDBUser:GVL5LZkVbxKzVFoB@myatlasclusteredu.6fevoas.mongodb.net/?retryWrites=true&w=majority&appName=myAtlasClusterEDU";

const client = new MongoClient(uri, {
  serverApi: {
    version: ServerApiVersion.v1,
    strict: true,
    deprecationErrors: true,
  }
});

client.connect();

/*------------------------------------------
--------------------------------------------
Shows Mysql Connect
--------------------------------------------
--------------------------------------------*/
conn.connect((err) =>{
  if(err) throw err;
  console.log('Mysql Connected with App...');
});

/**
 * Get All Items
 *
 * @return response()
 */

/*
MongoDB Endpoints
*/

// movies get request
app.get('/api/v1/movies', async(req, res) => {
  let result = [];
  try{
    let database = client.db("sample_mflix");
    let collection = database.collection("movies");
    if(req.query.genre){
      let objectId = req.query.genre;
      result = await collection.find({"genres": objectId}).limit(10).toArray();
    }
    else{
      result = await collection.find().limit(10).toArray();
        }

    res.send(result)
  } catch(err){
    console.error(`Something went wrong: ${err}\n`);
    res.send(["An error has occurred."])
  }

});

// /colors get request
app.get('/api/v1/colors', async(req, res) => {
  try{
    let database = client.db("cs480-project2");
    let collection = database.collection("colors");
    const result = await collection.find().toArray();

    res.send(result)
  } catch(err){
    console.error(`Something went wrong: ${err}\n`);
    res.send(["An error has occurred."])
  }

});

// /colors/<id> get request
app.get('/api/v1/colors/:id', async(req, res) => {
  try{
    let database = client.db("cs480-project2");
    let collection = database.collection("colors");
    let objectId = new ObjectId(req.params.id);
    const result = await collection.find({"_id": objectId}).toArray();

    res.send(result)
  } catch(err){
    console.error(`Something went wrong: ${err}\n`);
    res.send(["An error has occurred."])
  }

});

// /colors post request
app.post('/api/v1/colors', async(req, res) => {
  try{
    let data = {"color": "black"};
    let database = client.db("cs480-project2");
    let collection = database.collection("colors");
    const result = await collection.insertOne(data);
    res.send(result)
  } catch(err){
    console.error(`Something went wrong: ${err}\n`);
    res.send(["An error has occurred."])
  }

});

// /colors/<id> delete request
app.delete('/api/v1/colors/:id', async(req, res) => {
  try{
    let database = client.db("cs480-project2");
    let collection = database.collection("colors");
    let objectId = new ObjectId(req.params.id);
    let data = {"_id": objectId};
    const result = await collection.deleteOne(data);
    res.send(result)
  } catch(err){
    console.error(`Something went wrong: ${err}\n`);
    res.send(["An error has occurred."])
  }

});

/*
Sakila Database Endpoints
*/

// /actor get request
app.get('/api/v1/actors', (req, res) => {
  let sqlQuery = "SELECT * FROM actor;";

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /films get request
app.get('/api/v1/films',(req, res) => {
let sqlQuery = "";
  if (req.query.query){
    sqlQuery += "SELECT * FROM film where LOWER(title) like "  + conn.escape("%" + req.query.query.toLowerCase() + "%");
  }
  else{
    sqlQuery += "SELECT * FROM film;";
  }
  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    else {res.send(results);}
  });
});

// /customers get request
app.get('/api/v1/customers',(req, res) => {
  let sqlQuery = "SELECT * FROM customer;";

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /stores get request
app.get('/api/v1/stores',(req, res) => {
  let sqlQuery = "SELECT * FROM store;";

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /staff get request
app.get('/api/v1/staff',(req, res) => {
  let sqlQuery = "SELECT * FROM staff;";

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /actor/<id> get request
app.get('/api/v1/actors/:id',(req, res) => {
  let sqlQuery = "SELECT * FROM actor where actor_id =" 
   + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /film/<id> get request
app.get('/api/v1/films/:id',(req, res) => {
  let sqlQuery = "SELECT * FROM film where film_id =" 
   + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /customers/<id> get request
app.get('/api/v1/customers/:id',(req, res) => {
  let sqlQuery = "SELECT * FROM customer where customer_id =" 
   + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /stores/<id> get request
app.get('/api/v1/stores/:id',(req, res) => {
  let sqlQuery = "SELECT * FROM store where store_id =" 
   + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /staff/<id> get request
app.get('/api/v1/staff/:id',(req, res) => {
  let sqlQuery = "SELECT * FROM staff where staff_id =" 
   + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /inventory/<id> get request
app.get('/api/v1/inventory/:id',(req, res) => {
  let sqlQuery = "SELECT * FROM inventory where inventory_id =" 
   + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /actors/<id>/films get request
app.get('/api/v1/actors/:id/films',(req, res) => {
  let sqlQuery = "SELECT * FROM film inner join film_actor fm on film.film_id = fm.film_id inner join actor on fm.actor_id = actor.actor_id where actor.actor_id = " + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /films/<id>/<actors> get request
app.get('/api/v1/films/:id/actors',(req, res) => {
  let sqlQuery = "SELECT * from actor where actor_id in (SELECT actor.actor_id FROM actor inner join film_actor fm on actor.actor_id = fm.actor_id inner join film on fm.film_id = film.film_id where film.film_id = " + conn.escape(req.params.id) + ");";

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /films/<id>/detail get request
app.get('/api/v1/films/:id/detail',(req, res) => {
  let sqlQuery = "select * from film_list where FID =" + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /customers/<id>/detail get request
app.get('/api/v1/customers/:id/detail',(req, res) => {
  let sqlQuery = "select * from customer_list where ID =" + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /actors/<id>/detail get request
app.get('/api/v1/actors/:id/detail',(req, res) => {
  let sqlQuery = "select * from actor_info where actor_id =" + conn.escape(req.params.id);

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

// /inventory-in-stock/<film_id>/<store_id> get request
app.get('/api/v1/inventory-in-stock/:fid/:sid',(req, res) => {
  let sqlQuery = "call film_in_stock(" + conn.escape(req.params.fid) + ", " + conn.escape(req.params.sid) + ", @count);";

  let query = conn.query(sqlQuery, (err, results) => {
    if(err) res.send(["An error has occurred."]);
    res.send(results);
  });
});

/*------------------------------------------
--------------------------------------------
Server listening
--------------------------------------------
--------------------------------------------*/
app.listen(3000,() =>{
  console.log('Server started on port 3000...');
});