#version 330 core

in vec3 ourColor;//颜色输入
in vec2 TexCoord;//纹理输入

out vec4 FragColor;//片元颜色输出

//uniform sampler2D ourTexture;//sampler指采样器，用于将纹理添加到片段着色器中

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//texture()函数用于采样纹理颜色：
	//第一个参数是纹理采样器，第二个是对应的纹理坐标；
	//它会使用之前设置的纹理参数对相应的颜色值进行采样，使片段着色器输出纹理坐标差值计算后的颜色

	//FragColor = texture(ourTexture, TexCoord);//单纯纹理
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);//纹理与颜色的混合
	
	/*mix()函数第三个参数为对纹理颜色的线性插值(0-1之间，0表示只有第一种材质，1表示只有第二种材质)*/
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);//纹理和纹理的混合
}