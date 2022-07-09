# Requirements
- Node.js 

# Dependencies
 - body-parser ^1.18.3 
 - crypto-js   ^3.1.9-1
 - elliptic    ^6.4.0
 - express     ^4.16.3
 -  uuid       ^3.2.1
 -  WebSockets ^5.2.0
 
# Dev Dependencies

- jest ^23.1.0 
- nodemon ^1.17.5

# Installation

You can Run the following command using Terminal/CMD:
```
$npm install
```

# Usage

The API is built with NodeJS and Express.You can interact with the API.
<br>
For demonstration:

```Note :```Requires Nodemon
- Run the server:
  ```
  $npm run dev 
  ```
  Output :
  ```
  > nodemon ./app

  [nodemon] 1.17.5
  [nodemon] to restart at any time, enter `rs`
  [nodemon] watching: *.*
  [nodemon] starting `node ./app.js`
  Listening for Peer-to-Peer connections on port : 5000
  server started on port 3000


  ```
  
- To start another instance (peer)
  ```
  $ HTTP_PORT=3001 P2P_PORT=5001 PEERS=ws://localhost:5000 npm run dev
  ```
  Output :
  ```
   > nodemon ./app

   [nodemon] 1.17.5
   [nodemon] to restart at any time, enter `rs`
   [nodemon] watching: *.*
   [nodemon] starting `node ./app.js`
   Listening for Peer-to-Peer connections on port : 5001
   server started on port 3001
   Socket Connected!
   Received chain is not longer than the current chain.

  ```
# Methods  
- To get all the blocks of the blockchain 
 
  <strong>GET</strong> ```http://localhost:3000/blocks```
    
  Response:
  ```
  [
    {
        "timeStamp": "0",
        "lastHash": "0",
        "hash": "xxxxxxxx",
        "data": [],
        "nonce": 0,
        "difficulty": 4
    }
   ]
  ```
- To get own Public Key
 
  <strong>GET</strong> ```http://localhost:3000/publicKey```
    
  Response:
  ```
  {
    "PublicKey": "049130b76348c0ff2ff7c268f1c3344c50859309e9b767f34bd63e3683aa12bb3442cba91de6fd6e5f75868cdd955b0f34e23adfc305c18f39c54c2e588d361926"
  }
  ```
- Mine or add blocks to the blockchain
 
  <strong>POST</strong> ```http://localhost:3000/mine```
  
  JSON Input :
  ```
  {
  "data" : "foo-bar"
  }
  ```


  Response:
  ```
    [
    {
        "timeStamp": "0",
        "lastHash": "0",
        "hash": "xxxxxxxx",
        "data": [],
        "nonce": 0,
        "difficulty": 4
    },
    {
        "timeStamp": 1529268657715,
        "lastHash": "k1S2-P1s2",
        "hash": "000fa69a765a699bfc58c24781412ba738232f5af29e3bde0f9fba47d16d3006",
        "data": "foo-bar",
        "nonce": 7211,
        "difficulty": 3
    }
    ]
  ```
  
- To perform Transaction And Send Cryptocurrency using someone's Public key
 
  <strong>POST</strong> ```http://localhost:3000/transact```
  
  
   JSON Input :
  ```
  {
	"recipient" : "047648c967013eec3f332d103227eee7decde237cac3984bb9523f70f6cbc486060906f412f19039d70f8892a9b388a51664a740adca61e7386a038cb99ce42864",
	"amount"	: 50
  }
  ```
    
  Response:
  ```
  [
    {
        "id": "8676c910-7272-11e8-86ef-85c52672e7ed",
        "input": {
            "timeStamp": 1529269684257,
            "amount": 500,
            "address": "0423141eab6d1875ae22a96dac794328ba962913bdbbb6a7e1c9cfb4ffd0e7989fac58a722d79b4a5891fb8875831e20e9e54e58856ac074ef15eb7d6ef3a0a761",
            "signature": {
                "r": "861d22558e1387ea4e081c156dd796b24fd2ba783b218ffc7a853207f2361b68",
                "s": "cf5677f392142cd083df68189b3200a19e32e2ea1da34d63c2a188ef8a0a6186",
                "recoveryParam": 0
            }
        },
        "outputs": [
            {
                "amount": 450,
                "address": "0423141eab6d1875ae22a96dac794328ba962913bdbbb6a7e1c9cfb4ffd0e7989fac58a722d79b4a5891fb8875831e20e9e54e58856ac074ef15eb7d6ef3a0a761"
            },
            {
                "amount": 50,
                "address": "047648c967013eec3f332d103227eee7decde237cac3984bb9523f70f6cbc486060906f412f19039d70f8892a9b388a51664a740adca61e7386a038cb99ce42864"
            }
        ]
    }
  ]
  ```
  
- To get all valid transactions
 
  <strong>GET</strong> ```http://localhost:3000/transactions```
    
  Response:
  ```
   [
    {
        "id": "8676c910-7272-11e8-86ef-85c52672e7ed",
        "input": {
            "timeStamp": 1529269684257,
            "amount": 500,
            "address": "0423141eab6d1875ae22a96dac794328ba962913bdbbb6a7e1c9cfb4ffd0e7989fac58a722d79b4a5891fb8875831e20e9e54e58856ac074ef15eb7d6ef3a0a761",
            "signature": {
                "r": "861d22558e1387ea4e081c156dd796b24fd2ba783b218ffc7a853207f2361b68",
                "s": "cf5677f392142cd083df68189b3200a19e32e2ea1da34d63c2a188ef8a0a6186",
                "recoveryParam": 0
            }
        },
        "outputs": [
            {
                "amount": 450,
                "address": "0423141eab6d1875ae22a96dac794328ba962913bdbbb6a7e1c9cfb4ffd0e7989fac58a722d79b4a5891fb8875831e20e9e54e58856ac074ef15eb7d6ef3a0a761"
            },
.....
  ```
- Mine transactions to add rewards to the Miners
 
 <p>By default each miner will get 50 Reward points for mining </p>
 
  <strong>GET</strong> ```http://localhost:3001/mine-transactions```
    
  Response:
  ```
  [
    {
        "timeStamp": "0",
        "lastHash": "0",
        "hash": "xxxxxxxx",
        "data": [],
        "nonce": 0,
        "difficulty": 4
    },
    {
        "timeStamp": 1529270176969,
        "lastHash": "k1S2-P1s2",
        "hash": "00009971fd40b7bf881bf5972cef499ebdf1628d97457d599e2162d9dcf8a846",
        "data": [
            {
                "id": "8676c910-7272-11e8-86ef-85c52672e7ed",
                "input": {
                    "timeStamp": 1529269684257,
                    "amount": 500,
                    "address": "0423141eab6d1875ae22a96dac794328ba962913bdbbb6a7e1c9cfb4ffd0e7989fac58a722d79b4a5891fb8875831e20e9e54e58856ac074ef15eb7d6ef3a0a761",
                    "signature": {
                        "r": "861d22558e1387ea4e081c156dd796b24fd2ba783b218ffc7a853207f2361b68",
                        "s": "cf5677f392142cd083df68189b3200a19e32e2ea1da34d63c2a188ef8a0a6186",
                        "recoveryParam": 0
                    }
                },
                "outputs": [
                    {
                        "amount": 450,
                        "address": "0423141eab6d1875ae22a96dac794328ba962913bdbbb6a7e1c9cfb4ffd0e7989fac58a722d79b4a5891fb8875831e20e9e54e58856ac074ef15eb7d6ef3a0a761"
                    },
.....
  ```
# Integration Tests

You can run integration tests using the following command :
   ```
   $npm run test
   ```
   ```Note ```: Testing requires <a href="https://facebook.github.io/jest/">JEST</a>
   

