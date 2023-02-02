cd
C:\VulkanSDK\1.3.236.0\Bin\glslc.exe .\shaders\shader.vert -o .\shaders\vert.spv && echo "Vertex shader compiled succesfully" || echo "Vertex shader: compiler ran into an error"
C:\VulkanSDK\1.3.236.0\Bin\glslc.exe .\shaders\shader.frag -o .\shaders\frag.spv && echo "Fragment shader compiled succesfully" || echo "Fragment shader: compiler ran into an error"
