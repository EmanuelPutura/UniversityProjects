# Football Team Squad Management Mobile App

## Lab Requirements
The lab plan can be found [here](http://www.cs.ubbcluj.ro/~dan/ma/labPlan.html).

### Non-Technical Overview
This is a mobile application for handling the squad of players of a football team. The user should be able to check all the team players, add (transfer) a new player to 
the team, delete an existing player, or update the data of a football player from the team. 
On the main screen, the user should be able to check all the available players in the squad. There should also be a button that, if pressed, takes the user to a different 
page, where he/she will be able to add a new player to the squad. When pressing on a list entry from the main page, the user will be prompted to a page where all the 
corresponding player's details will be shown. Moreover, the user will have the possibility to update these details or delete the player.

### Problem Domain Overview
Entity that will be persisted: `Football Player`<br />
Fields of the entity:
- `name:`       string      - the name of the player (first name + last name)
- `position:`   string      - the field position of the player (e.g., GK, CB, LB, RB, ST)
- `number:`     integer     - the shirt number of the player. N can be a shirt number, if and only if 1 <= N <= 99
- `height:`     integer     - the height of the player, in centimeters
- `weight:`     double      - the weight of the player, in kilograms

### Actions - CRUD Operations
The following operations should be supported by the application:
- `create/add:` creates and adds a new football player to the squad of the team
- `read:`       view the set of football players that are currently enrolled in the team
- `update:`     allow the user to update a football player found in the list. The user can update any fields of the football player
- `delete:`     delete existing football players from the list. This happens when the football player is transferred (sold) to a different team

### Persistence Details
All the available operations will be persisted on the local db and on the server (i.e., create/add, delete, update).

### Offline App Handling
The application should persist the content locally, to be able to allow offline access. While online, it should synchronize the content with a remote 
server. While offline the application will perform the following actions:
- on `update:` a message will be displayed, that the application is offline and the operation is not available
- on `delete:` a message will be displayed, that the application is offline and the operation is not available
- on `read:` the content from the local database will be displayed, with a note that the server connection is down
- on `create:` the input will be persisted in the local database and when the application will detect that the device is able to connect again to the server it 
will push only the created entries, while the device was offline

### App Mockup
You can check the initially proposed design of the app [here](https://www.figma.com/file/52vK9XPCyZk7cGbwV7MdDx/FCSB-MobileApp?node-id=0%3A1).

#### Main Screen
![image](https://user-images.githubusercontent.com/72196173/197035013-fdcf4c06-687f-4c58-b8ad-ad9c547f93b1.png)

#### CRUD Screen
![image](https://user-images.githubusercontent.com/72196173/197035104-0b09a87b-a69c-47bf-957f-98df5f7b1fc5.png)

