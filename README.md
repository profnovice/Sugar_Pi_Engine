# Ongoing cross-platform game engine from scratch using CMake SFML Project Template

Learning process with C++, SFML, imgui-sfml, CMake, etc.

## General Architecture 

A basic Entity Component System layout where entity memory allocation and deallocation is handled exclusivly by an entity manager.    
Components only store data and the systems in the game loop act on that data.   
Components include CTransform, CCollision, CRidgedBody, CInput, and more.    
Pulling heavily from Dave Churchill's excellent COMP4300 - Game Programming video series on YouTube.   

## Git commit format

### Example:

feat(src): Add new jump ability 

Testers were bored while in the air so this flip ability should 
give them something to do.

### Flags:

- chore: typos, documentation
- style: reformatting, rearranging
- feat: new feature, system
- fix: solution to an issue
- refac: making it better without changing what it does
- test: check to see that things run correctly
- explr: experiment with libraries and new features
- clean: remove unnecessary code or comments

### Areas:

- git: workflows
- docs: README and LICENSE, etc.
- src: source code
- assets: textures, config, .ttf, etc.
- tool: tools, libraries, build systems, etc.

### Creed: 

- Separate subject from body with a blank line
- Limit the subject line to 50 characters
- Capitalize the subject line
- Do not end the subject line with a period
- Use the imperative mood in the subject line: "if applied this commit will"
- Wrap the body at 72 characters
- Use the body to explain what and why vs. how
