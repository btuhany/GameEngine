- In order to enabe light shadows, shadow map constructor must be used and shadow shader must set.
- If shadow maps are going to be used, shadow shaders must be set.
- 2D scenes -> scene edges m_FOV * aspectRatio 
*******************************************
********** NAMING CONVENTION **************
private member -> m_PrivateMember
public member -> publicMember
private function -> privateFunction()
public function -> PublicFunction
get and set functions -> getOrSetFunction()
*******************************************

************************************************************
******************** TODO **********************************
- [] CREATE MAKE FILE
- [] Renderer components with render date template (or abstract components with data)
- [] Engine starting settings static class (set DEBUG_MODE and shadow modes from a single place)
- [] Fix anonim calls for events
- [] Collider scale and doesn't scale with transform scale
- [] Abstract entity/components which use Initialize, Start, Tick
- [] Abstract managers (renderer, textRenderer, collision manager)
- [] Check type of component when adding to entity if there is any same type
- [] MeshData and TextData base class (Abstract mesh data class)
- [] FPS limit fix
- [] UI Renderer abstraction, polymorphism fix
- [] Sprite render data material dependency, using the same mesh data instance
- [] Not instantiated components still contained in manager vector lists. Components should be registered to System Manager after instantiated (for example: RendererComponent and Renderer)
- [] Camera space ui canvas
- [] JSON Serialization/Deserialization
- [] Application quit handler
- [] Multiple scenes / transitions
- [] Text Renderer custom fonts, refactor
************************************************************

08.24
TODO: Create a RenderableObject base class that contains a Renderer an calls Render() function [X]

02.09.24
TODO: 
- Create a ModelEntity class and render models with model entity, than refactor classes [X]
- Refactor scene render handling  [O]

09.09.24
TODO:
- Refactor scene render handling  [X]
 
23.09.24
TODO:
- review shared and weak pointer usages [O]
- Deleting an object, deleting component references from list [O]
- Sending component add event with component type, handling in entity add component, rendering renderer components if entities's instantiate confirmed[X]

29.09.24
TODO:
- review shared and weak pointer usages [X]
- Deleting an object, deleting component references from list [X]
- Review overall render data transfers [O]

6.10.24
TODO:
- review shared and weak pointer usages [X]
- Review overall render data transfers [X]
- Review scene class [X]

13.10.24
- review scene class again [X]
- review entry point [X]
- start engine visual diagram [CANCEL]

daily 29.10.24 
- BoxCollider2D debugger [X]
- Collider check with scales[X]
- Collider callbacks [X]
- GameObject destroy renderer system check [X]
- GameObject destory collision system check [X]

29.10.24
- publishing event of object deactivating/activating and listening from managers [X]
- Fixing input lag due to thread sleep []

03.11.24
- Renderer code review []
- Tags for entities []
- Transparent sprites [x]

16.11.24
- Renderer code review [O]
- Tags for entities [O]
- TEXT RENDERER [O]
- Update method frame time calculations [O]

1.12.24
- Reversed aspect ratio fix [?]
- Text transparent color fix [X]
- TEXT RENDERER [X]
daily
- [X] FPS Fix

BREAKOUT GAME
- Game Manager [X]
- Paddle Collider Normals fine tuning fix [X]
- Fix temp isInCollider bool for ball [X]
- Process all colliders at once [CHANGED]
- Main menu -> Play and Quit [X]
- Ball rotation animation [X]
- Bricks transition animation [X]
- Finalizing design [X]
- Overall level transitions logic [X]
- Player lost lives logic [X]
- Pause logic -> Back to main menu [X] (CHANGED)
- Tiles calculating normals based on ball movement vector [X]
- Starting ball movement vector based on paddle speed [X]
- BreakoutObject refactor (consider Brick)
- Initializing data with config classes (without magic numbers) []
- Refactor (abstraction, polymorphism) []