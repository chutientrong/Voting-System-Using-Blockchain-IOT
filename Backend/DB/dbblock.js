// var db = require('../DbConnection');


// var DbBlocks = {
//     getAllBlock: function(callback) {
//         return db.query("Select * from blocks", callback);
//     },
//     getBlockById: function(index, callback) {
//         return db.query("select * from blocks where ID=?", [index], callback);
//     },
//     addBlock: function(blocks, callback) {
//         return db.query("Insert into blocks (timestamps,previous_hash,hash,data,nonce,difficulty) values(?,?,?,?,?,?)", [blocks.timeStamp, blocks.lastHash, blocks.hash, blocks.data, blocks.nonce, blocks.difficulty], callback);
//     },
//     // deleteBlock: function(index, callback) {
//     //     return db.query("delete from blocks where indexs=?", [index], callback);
//     // },
//     // updateBlock: function(index, blocks, callback) {
//     //     return db.query("update blocks set index=?,previous_hash=?,data=?,timestamps=?,hash=? where Id=?", [blocks.index, blocks.previousHash, blocks.data, blocks.timestamp, blocks.hash, id], callback);
//     // }
// };

// module.exports = DbBlocks;
