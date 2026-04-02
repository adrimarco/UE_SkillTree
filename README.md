# UE_SkillTree
This project is focused on the creation of a simple skill tree with unlockable skills, but it also contains other UI elements to make a more complete HUD. This document explains the different widgets that form the HUD, their purpose, and a short explanation of how they have been implemented. Overall, the character and the HUD are separated, mainly using events to update data in the HUD and avoiding direct references as much as possible.

All UI widget classes are created in C++, where their functionality is implemented. Then, a derived widget blueprint is created to define the appearance of the UI elements, as it is faster and easier than using code. Blueprints are only used to configure the visual aspect and create animations for the UI, while all functionality remains in C++. To showcase the skill tree and the other UI elements, a test map with a simple "game" has been implemented. All gameplay elements have been implemented using C++ as well.

C++ files can be found in the Source folder. UI widget blueprints are stored in the Content/UI folder, which also includes the textures used in the skills and the data table with the skills values. All other important blueprints for the gameplay can be found next to the character in the Content/ThirdPerson/Blueprints folder.

## Contents
- [Skill Tree](#skill-tree)
- [Buttons and Modal Message](#buttons-and-modal-message)
- [Other UI Widgets](#other-ui-widgets)
- [Player HUD](#player-hud)
- [Gameplay](#gameplay)
- [Test Map](#test-map)
- [Conclusion](#conclusion)

## Skill Tree
The most important part, the skill tree, has been implemented mainly with two C++ clases:

### Skill Slot
This class contains the visual representation of a skill in the tree and includes events that are called when the skill is selected. It also contains references to some animations and style variables that are applied when the skill is unlocked/blocked. Each skill can have an ID, which is used later to identify it and fill the information. To create a hierarchy of skills, a previous skill can be assigned as a reference so that the skill cannot be unlocked until the previous one is unlocked, which is visually represented with a line that connects the skills and applying different colors. This widget contains the elements that are displayed in the skill tree for each skill and encapsulates the visual behaviour of the slots, such as controlling dependencies and playing animations when unlocked, but the functionality is controlled by the skill tree display.

### Skill Tree Display
This class is responsible for controlling the events in the skill tree, updating data, and applying the effects of the skills. The widget itself is mainly a container panel with all the skills. The skill slots are placed in the panel in any position to create the visual representation of the tree. To create the hierarchy, all skills except the initial ones must have a previous skill assigned. Skills do not require individual configuration because a data table with the skill data must be provided, so that when the tree is created, it iterates through the skill slots to update their image and other properties with the information from the data table. This allows modifying the skill parameters by updating the data table without having to update the skill tree widget. For this to work, the skill slots must have an ID assigned that must be present in the data table. Moreover, the slots do not store any information about their skill to avoid duplicated data. Instead, the skill tree is responsible for managing the actions.

When a skill is selected, the skill tree class searches the skill data in the data table using the slot ID and displays a modal message with it, if required. When unlocking a skill, if the player has enough points, a lambda is bound to the modal message so that it updates the skill points, modifies the skill slot appearance and applies the skill to the player when the action is confirmed.

Apart from the skills, the skill tree contains a text that displays the current amount of skill points the player has and a reset button that appears after unlocking the first skill. The reset button allows the player to return the unlocked skills and recover spent skill points. To confirm this action, a modal message appears after pressing it as well.

## Buttons and Modal message
All buttons in the HUD are implemented as a hold button (named HoverButton) that requires the user to keep the button pressed for a specific amount of time in order to work. The required time can be configured, and when the button is held long enough, an event is called, so it must be bound to execute an action when this happens. The button contains a progress bar that is updated to show the time the button has been held. To implement a standard button, the time required to "press" the button is set to 0, so it sends the "pressed" event instantly. It could have been implemented with a base button class and then creating a hold button that modifies its behaviour, but once the hold button was implemented, setting its required time to 0 worked perfectly, so there was no need to change it, although it could be refactored. The button can also be enabled or disabled, playing a special animation in this last case without executing any action.

The modal message appears when trying to perform actions that require confirmation, such as unlocking a skill or resetting the skill tree. This widget is drawn on top of the others to prevent any other element from being clicked when it appears and has 3 elements: a text, a confirm button and a cancel button. The cancel button closes the modal message without doing anything else, while the confirm button sends an event before closing the modal message. Any action that must be confirmed can be bound to this event so that it is executed only when the confirm button is pressed. This class contains a function to easily modify the confirm button's text, hold time, or disable the button.

## Other UI Widgets
Apart from the skill tree, other widgets were implemented to complete the HUD and display more information about the player.

### Stats Display
The PlayerStats is a container that has "tags" with the player's stats. These tags (named StatValue) are made of an image and a text. The container class has a function that allows the player to hide/show the stats at any moment, modifying the visibility of the widgets. It also binds several functions to the player's events so that the widgets are updated any time their attributes change, for instance, when a skill is unlocked.

### Notification
The HUD contains a tag that is used to display notifications to the player. This appears on the screen with an animation and fades away after a short time. Although a new widget class with more complex functionality could have been implemented to create a more flexible notification system, it was implemented using a StatValue tag and an animation in the HUD class, as this is only used to notify when the player obtains a skill point.

### Charges Display
As the player has an ability with limited uses, a widget that represents the ability's charges has been implemented. The ChargesDisplay widget has a container and a reference to a widget class (named ChargeIcon). When the player unlocks the ability and upgrades it, the widget creates child widgets that are added to the container, each one representing the number of uses the ability has. When the player uses the ability or recovers the charges, it is displayed with animations in the container, which are controlled by the created child widgets.

### Billboard
A basic widget called TextDisplay is used to display a text block in a widget. This is used by a billboard actor to display the widget in the world. This can be configured to always face the camera, like a billboard, or remain static.

## Player HUD
All HUD elements mentioned before (except for the Billboard) are inside a widget called PlayerHud. This is the widget that is added to the player's viewport and is responsible for binding the input to open/close the skill tree and the player stats display. It also exposes a reference to the modal message to be used by other widgets that need it and a function to display a notification, which, as mentioned before, is only used to notify when the player obtains skill points.

## Gameplay
To test the skill tree, a simple level has been created to obtain skill points and upgrade the character by unlocking skills. These features have been coded in C++, as the UI.

### Character
The player's character is based on Unreal's Third Person Character but includes variables to configure the HUD that is added to the player. When this happens, all events that notify any attribute change are called so that the HUD is updated, for example, the PlayerStats display. The character also has an ability to interact with platforms that requires charges to be used. It stores the ability charges and the skill points acquired and has functions to access and modify them.

When an ability is unlocked, a character function is called to apply its effects. Due to the simplicity of the skills, this function updates variables depending on an enum that specifies the skill type and a float value. Moreover, it has another function that undoes the effects of a skill, which is used when the skill tree is reset.

### Checkpoints
Checkpoints are triggers with a particle system that provide an easy progression system to test the skill tree. Their main purpose is granting skill points to the player the first time they are activated, allowing the player to unlock more skills every time they reach a new one. Additionally, every time the player enters a checkpoint, their ability charges are refilled and their respawn location is changed, so that if they fall off the map, they move to this location. A kill trigger (named OffLimitTrigger) implements the functionality of moving the player to their respawn location when they touch it.

### Elevator
This actor is an interactable element the player can use once they unlock their ability. It is basically a platform that stands still in a position until it is activated. At that moment, the platform starts to rise and, after that, gravity pulls it back to its original position. It can be activated multiple times to get even higher.

## Test Map
The test map (Content/ThirdPerson/Lvl_ThirdPerson) is basically a huge ramp with some checkpoints on the way that provide skill points to upgrade the character and reach the end faster. The ramp has some tall blocks and platforms that can be used after unlocking some skills to shorten the path. The movement speed can also be increased. From the start of the map, different billboard widgets in the world explain the controls to test the UI. These are the controls:

- WASD: Move
- Mouse: Look
- Space: Jump
- TAB: Open/Close Skill Tree
- Q: Show/Hide Player Stats
- Skill tree nodes and buttons can be selected with the mouse.

Although the test map is really short and can be completed in a couple of minutes, if you do not want to go to the checkpoints to get the skill points, you can change the initial skill points manually in the ThirdPersonCharacter (Content/ThirdPerson/Blueprints folder), as well as the max charges, to be able to use the ability from the start.

## Conclusion
This project showcases a simple implementation of a skill tree using C++ for the core functionality and Blueprints for the visuals and animations of the UI. It features a basic separation of visual representation and data to make a more flexible system, allowing faster modification of skill parameters without changing the widgets themselves. It also connects the character and the HUD through events to minimize direct references between them. However, more abstraction could be done to encapsulate the different "parts" of the game and reduce dependencies between the UI widgets.