- In order to enabe light shadows, shadow map constructor must be used and shadow shader must set.
- If shadow maps are going to be used, shadow shaders must be set.
- 2D scenes -> scene edges m_FOV * aspectRatio 
*******************************************
********** NAMING CONVENTION **************
private member -> m_PrivateMember
public member -> privateMember
private function -> privateFunction()
public function -> PublicFunction
get and set functions -> getOrSetFunction()
*******************************************

************************************************************
******************** TODO **********************************
- [] Renderer components with render date template
- [] Engine starting settings static class (set DEBUG_MODE and shadow modes from a single place)
- [] Fixing input lag due to thread sleep
- [] Fix anonim calls for events
- [] Collider scale and doesn't scale with transform scale
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

29.10.24 daily
- BoxCollider2D debugger [X]
- Collider check with scales[X]
- Collider callbacks [X]
- GameObject destroy renderer system check [X]
- GameObject destory collision system check [X]

- 29.10.24
- publishing event of object deactivating/activating and listening from managers [X]
- Fixing input lag due to thread sleep []

- 03.11.24
- Renderer code review fix []