
MOAISim.openWindow("game", 1024, 1024)

viewport = MOAIViewport.new()
viewport:setSize (1024, 1024)
viewport:setScale (1024, -1024)

layer = MOAILayer2D.new()
layer:setViewport(viewport)
MOAISim.pushRenderPass(layer)

texture_name = "dragon.png"
gfxQuad = MOAIGfxQuad2D.new()
gfxQuad:setTexture(texture_name)
char_size = 64
gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
gfxQuad:setUVRect(0, 0, 1, 1)

prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)

entity = Character.new()
-- Add prop to be the renderable for this character
entity:setProp(prop, layer)
-- Start the character (allow calls to OnUpdate)
entity:start()
entity:setLoc(-150, -150)
entity:setRot(0)
entity:setLinearVel(0, 0)
entity:setAngularVel(0)


-- Enable Debug Draw
debug = MOAIDrawDebug.get();
layer:setDrawDebug(debug)
-- Add this character to draw debug

pathfinder = Pathfinder.new()
pathfinder:setCharacter(entity)

pathfinder:setStartPosition(-175, -175)
pathfinder:setEndPosition(175, -175)
MOAIDrawDebug.insertEntity(entity)
MOAIDrawDebug.insertEntity(pathfinder)

mouseX = 0
mouseY = 0

function onClickLeft(down)
 pathfinder:setStartPosition(mouseX, mouseY)
end

function onClickRight(down)
 pathfinder:setEndPosition(mouseX, mouseY)
end

function pointerCallback(x, y)
    mouseX, mouseY = layer:wndToWorld(x, y)
end

MOAIInputMgr.device.mouseLeft:setCallback(onClickLeft)
MOAIInputMgr.device.mouseRight:setCallback(onClickRight)
MOAIInputMgr.device.pointer:setCallback(pointerCallback)