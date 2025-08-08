# KeyValue store

 Simple REST server that allows to use as in-memory key-value storage  
 But when server starts - storage is empty

 You can import routes for Insomnia [here](./assets/insomnia_microrest.yaml)

## Routes

 ### POST /add
 ![](./assets/0.jpg)
 
 Add new key-value pair
 
### POST /get
 
 ![](./assets/1.jpg)
 ![](./assets/2.jpg)

 Return value by key
 
### DELETE /del

![](./assets/3.jpg)
![](./assets/4.jpg)

 Remove pair
 
### GET /keys

![](./assets/5.jpg)

 Return array of keys, if no keys available return empty array
 
### GET /

![](./assets/6.jpg)

Return all data in json format

### Server output

![](./assets/7.jpg)

Server have simple but useful logging for requests and responses to debug