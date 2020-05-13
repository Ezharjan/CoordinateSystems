/*
创建一个正射投影矩阵
参数分别为平截头体的左右坐标、底部、顶部以及近和远平面的距离
ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

创建一个定义了可视空间的大平截头体
第一个参数是视野，设置了观察空间大小
第二个是宽高比
后面是平截头体的近和远平面
mat4 proj = perspective(radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
*/

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLMATH/glm.hpp>
#include <GLMATH/gtc/matrix_transform.hpp>
#include <GLMATH/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <std_image.h>
#include <shader_s.h>
#include <iostream>
using namespace std;
using namespace glm;

/*对窗口注册一个回调函数，它在每次窗口大小被调整时使用*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)//参数为窗口对象和新窗口的维度
{
	glViewport(0, 0, width, height);//告诉OpenGL渲染窗口的尺寸大小，即视口；前两个参数是窗口左下角的位置，后两个参数是窗口的宽和高
}

/*实现输入控制*/
void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//检查用户是否按下返回键(Esc)，按下返回GLFW_PRESS；否则返回GLFW_RELEASE
	{
		glfwSetWindowShouldClose(window, true);//将glfwSetWindowShouldClose设定为true以关闭GLFW
	}
}

int main()
{
	glfwInit();//初始化GLFW

	/*glfwWindowHint用于配置GLFW，第一个参数是选项名称，第二个是设置选项的一个整形的值*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设定主版本号为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设定次版本号为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//告诉GLFW使用核心模式

	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnWindow", NULL, NULL);//创建一个窗口对象，参数分别为宽、高、窗口名称，后两个暂时忽略
	if (window == NULL)
	{
		cout << "创建窗口失败" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//将窗口上下文设置为当前线程的主上下文

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册回调函数，告诉GLFW使每次窗口大小调整时调用该函数(自动填充里面的参数)

	/*初始化GLAD以在后面调用OpenGL函数*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//glfwGetProcAddress是用于加载系统相关的OpenGL函数指针地址的函数(必须在设定好线程上下文之后调用)
	{
		cout << "初始化GLAD失败" << endl;
		return -1;
	}

	Shader ourShader("shader.vert", "shader.frag");

	//float vertices[] = {
	//	//顶点				 //纹理坐标
	//	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
	//	0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
	//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
	//   -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
	//};

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	/*定义多个立方体在世界空间的位置*/
	vec3 cubePositions[] =
	{
	  vec3(0.0f,  0.0f,  0.0f),
	  vec3(2.0f,  5.0f, -15.0f),
	  vec3(-1.5f, -2.2f, -2.5f),
	  vec3(-3.8f, -2.0f, -12.3f),
	  vec3(2.4f, -0.4f, -3.5f),
	  vec3(-1.7f,  3.0f, -7.5f),
	  vec3(1.3f, -2.0f, -2.5f),
	  vec3(1.5f,  2.0f, -2.5f),
	  vec3(1.5f,  0.2f, -1.5f),
	  vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int VBO;//声名一个顶点缓冲对象
	unsigned int VAO;//声名一个顶点数组对象

	glGenBuffers(1, &VBO);//使用glGenBuffers函数和一个缓冲ID生成一个VBO
	glGenVertexArrays(1, &VAO);//创建一个顶点数组对象

	glBindVertexArray(VAO);//绑定VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将创建的缓冲绑定到GL_ARRAY_BUFFER(顶点缓冲对象的缓冲类型)上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*
	glVertexAttribPointer用于告诉OpenGl如何解析顶点数据
	第一个参数是要配置的顶点属性(着色器中定义了position顶点属性位置值(location))
	第二个是指定顶点属性的大小(三维向量，即大小为3)
	第三个是数据类型(向量的值由浮点组成)
	第四个为是否希望数据被标准化
	第五个是步长，即连续的顶点属性组之间的间隔(即x\y\z的值之间距离，每个占3个浮点型长度)
	最后一个是数据在缓冲中起始位置的偏移量(类型为void*)
	*/

	/*位置属性*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*纹理属性*/
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑VBO
	//glBindVertexArray(0);//解绑VAO

	/*创建纹理*/
	unsigned int texture1, texture2;

	glGenTextures(1, &texture1);//第一个参数是要生成纹理的数量，第二个是用于储存纹理的unsigned int数组
	glBindTexture(GL_TEXTURE_2D, texture1);//绑定纹理

	/*
	设置纹理环绕方式，纹理坐标轴为s和t
	第一个参数是纹理目标；第二个是指定设置的选项和应用的纹理轴；最后是环绕方式
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*设置纹理过滤选项*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//在纹理被缩小的时候使用邻近过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//在纹理被放大时使用线性过滤

	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);//选择GL_TEXTURE_BORDER_COLOR作为环绕方式时，需指定颜色

	stbi_set_flip_vertically_on_load(true);//设定加载图片时反转y轴

	/*加载图片*/
	int width, height, nrChannels;
	unsigned char* data = stbi_load(("Resources/Textures/wall.jpg"), &width, &height, &nrChannels, 0);//第一个参数是图像文件位置；后面三个参数是图像的宽度、高度和颜色通道的个数
	if (data)//如果图片加载成功
	{
		/*
		使被绑定的纹理对象被附加上纹理图像
		第一个参数是纹理目标，GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理；
		第二个参数为纹理指定多级渐远纹理的级别；0是基本级别；
		第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值；
		第四个和第五个参数设置最终的纹理的宽度和高度；
		第六个参数填0；
		第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组；
		最后一个参数是真正的图像数据
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理
	}
	else
	{
		cout << "加载纹理失败！" << endl;
	}
	stbi_image_free(data);//生成了纹理和相应的多级渐远纹理后，释放图像的内存

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*加载图片*/
	data = stbi_load(("Resources/Textures/awesomeface.png"), &width, &height, &nrChannels, 0);//第一个参数是图像文件位置；后面三个参数是图像的宽度、高度和颜色通道的个数
	if (data)//如果图片加载成功
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "加载纹理失败！" << endl;
	}
	stbi_image_free(data);//生成了纹理和相应的多级渐远纹理后，释放图像的内存

	ourShader.use();

	/*两种设置uniform的方法*/
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	ourShader.setInt("texture2", 1);

	//mat4 model;
	//mat4 view;
	//mat4 projection;

	//model = rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));//声名一个模型矩阵
	//view = translate(view, vec3(0.0f, 0.0f, -3.0f));//声名一个观察矩阵
	//projection = perspective(radians(45.0f), (float)(1280 / 720), 0.1f, 100.0f);//声明一个投影矩阵

	//unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
	//unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	//ourShader.setMat4("projection", projection);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//采用线框模式渲染

	glEnable(GL_DEPTH_TEST);//开启深度缓冲

	/*渲染循环*/
	while (!glfwWindowShouldClose(window))//glfwWindowShouldClose函数将检查GLFW是否被要求退出
	{
		process_input(window);//检查输入

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕所用的颜色
		//glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//同时清理颜色与深度缓冲

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();

		//mat4 model;
		mat4 view;
		mat4 projection;

		//model = rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));
		projection = perspective(radians(45.0f), (float)(1280 / 720), 0.1f, 100.0f);

		//unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		ourShader.setMat4("projection", projection);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)/*对十个箱子的进行不同的模型坐标系下的变换*/
		{
			mat4 model;
			model = translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);//交换颜色缓冲以绘制
		glfwPollEvents();//检查是否有事件被触发并更新窗口状态以及调用对应的回调函数
	}

	/*删除对象*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();//释放/删除之前分配的所有资源

	return 0;
}