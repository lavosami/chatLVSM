# db package

- **db** - startup package with functions, which would create new `db.sqlite3` file on startup of a server
- **client** - methods and functions for ***client*** table in database
- **message** - methods and functions for ***message*** table in database
- **user** - methods and functions for ***user*** table in database

## The last 3 packages should have methods:

- add (`addUser()`, `addMessage()`, `addChat()`)
- delete (`deleteUser()`, `deleteMessage()`)
- get (`getUser()`, `getMessages()`, `getChat()`)
- edit (`editUser()`, `editMessages()`)
