- In order to enabe light shadows, shadow map constructor must be used and shadow shader must set.
- If shadow maps are going to be used, shadow shaders must be set.
- Key release state is broken
- Mesh Renderers should be initialized before the start

TODO: Create a RenderableObject base class that contains a Renderer an calls Render() function