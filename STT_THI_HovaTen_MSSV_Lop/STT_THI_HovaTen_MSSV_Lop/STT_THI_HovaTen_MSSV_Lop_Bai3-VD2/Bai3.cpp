//khai báo và định thư viện stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// Include GLEW
#include <GL/glew.h>

//
#include "Shader.h"
#include "Camera.h"
// Include GLFW
#include <GLFW/glfw3.h>

//include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLFWwindow* window;
//function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

//window
const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;
//camera
Camera camera(glm::vec3(0.0f, 5.0f, 300.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
//khai báo kích thước hình cần vẽ (hình hộp chữ nhật)
float chieucao = 100.0f;
float chieurong = 10.0f;
float chieudai =10.0f;
float x_LP = 0.0f;
float y_LP = 0.0f;
float z_LP = 0.0f;
//khai báo kích thước Plane (của mặt phẳng)
float chieurong_Plane = 100.0f;
float chieudai_Plane = 200.0f;
float x_plane = 0.0f;
float y_plane = 0.0f;
float z_plane = 0.0f;
////timing
float deltaTime = 0.0f; //thời gian giữa khung hình hiện tại và khung hình sau
float lastframe = 0.0f;  //thời gian khung hình cuối

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Tạo 1 cửa sổ GLFWwindow 
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bai thi: STT_THI_HovaTen_MSSV_Lop_Bai3", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Đặt biến glewExperimental về true  (bắt buộc)
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	//cấu hình trạng thái opengl
	glEnable(GL_DEPTH_TEST);

	// Định nghĩa kích thước viewport
	 // Define the viewport dimensions
	int widthW, heightW;
	glfwGetFramebufferSize(window, &widthW, &heightW);    // lấy kích thước framebuffer   (chú ý)
	glViewport(0, 0, widthW, heightW);

	//khởi tạo shader
	Shader ourShader("vShader_b7.vertex", "fShader_b7.frag");



	//bước 1: khai báo vertex input (vertex data)
	//Mặt phẳng XOZ
	float planeVertices[] = {
		//tam giac 1
		//positions                                                      texture
		x_plane+chieurong_Plane/2,y_plane ,z_plane+chieudai_Plane/2,    1.0f,1.0f,
	   x_plane-chieurong_Plane/2,y_plane,z_plane + chieudai_Plane/2,   0.0f,1.0f,
	   x_plane -chieurong_Plane/2,y_plane,z_plane -chieudai_Plane/2,  0.0f,0.0f,
	   //tam giac 2
	   //positions                                texture
	   x_plane+chieurong_Plane/2,y_plane ,z_plane+chieudai_Plane/2,     1.0f,1.0f,
	   x_plane -chieurong_Plane/2,y_plane ,z_plane -chieudai_Plane/2,   0.0f,0.0f,
	  x_plane+ chieurong_Plane/2,y_plane ,z_plane -chieudai_Plane/2,    1.0f,0.0f,

	};
	
	GLfloat vertices_DoituongLapPhuong[] = {
		// vị trí - position         //texture coordinate (s,t)(u,v)
		          //x       y     z       u     v
			x_LP-chieurong/2,y_LP -chieucao/2,z_LP -chieudai/2,  0.0f, 0.0f,
			x_LP+ chieurong / 2, y_LP -chieucao / 2, z_LP -chieudai / 2,  1.0f, 0.0f,
			x_LP+chieurong / 2, y_LP+ chieucao / 2, -chieudai / 2,  1.0f, 1.0f,
			 chieurong / 2,  chieucao / 2, -chieudai / 2,  1.0f, 1.0f,
			-chieurong / 2,  chieucao / 2, -chieudai / 2,  0.0f, 1.0f,
			-chieurong / 2, -chieucao / 2, -chieudai / 2,  0.0f, 0.0f,

			-chieurong / 2, -chieucao / 2,  chieudai / 2,  0.0f, 0.0f,
			 chieurong / 2, -chieucao / 2,  chieudai / 2,  1.0f, 0.0f,
			 chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 1.0f,
			 chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 1.0f,
			-chieurong / 2,  chieucao / 2,  chieudai / 2,  0.0f, 1.0f,
			-chieurong / 2, -chieucao / 2,  chieudai / 2,  0.0f, 0.0f,

			-chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 0.0f,
			-chieurong / 2,  chieucao / 2, -chieudai / 2,  1.0f, 1.0f,
			-chieurong / 2, -chieucao / 2, -chieudai / 2,  0.0f, 1.0f,
			-chieurong / 2, -chieucao / 2, -chieudai / 2,  0.0f, 1.0f,
			-chieurong / 2, -chieucao / 2,  chieudai / 2,  0.0f, 0.0f,
			-chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 0.0f,

			 chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 0.0f,
			 chieurong / 2,  chieucao / 2, -chieudai / 2,  1.0f, 1.0f,
			 chieurong / 2, -chieucao / 2, -chieudai / 2,  0.0f, 1.0f,
			 chieurong / 2, -chieucao / 2, -chieudai / 2,  0.0f, 1.0f,
			 chieurong / 2, -chieucao / 2,  chieudai / 2,  0.0f, 0.0f,
			 chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 0.0f,

			-chieurong / 2, -chieucao / 2, -chieudai / 2,  0.0f, 1.0f,
			 chieurong / 2, -chieucao / 2, -chieudai / 2,  1.0f, 1.0f,
			 chieurong / 2, -chieucao / 2,  chieudai / 2,  1.0f, 0.0f,
			 chieurong / 2, -chieucao / 2,  chieudai / 2,  1.0f, 0.0f,
			-chieurong / 2, -chieucao / 2,  chieudai / 2,  0.0f, 0.0f,
			-chieurong / 2, -chieucao / 2, -chieudai / 2,  0.0f, 1.0f,

			-chieurong / 2,  chieucao / 2, -chieudai / 2,  0.0f, 1.0f,
			 chieurong / 2,  chieucao / 2, -chieudai / 2,  1.0f, 1.0f,
			 chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 0.0f,
			 chieurong / 2,  chieucao / 2,  chieudai / 2,  1.0f, 0.0f,
			-chieurong / 2,  chieucao / 2, chieudai / 2,  0.0f, 0.0f,
			-chieurong / 2,  chieucao / 2, -chieudai / 2,  0.0f, 1.0f

	};


	/// khai báo vị trí của các cube trong tọa độ thế giới
	glm::vec3 List_CubePosition[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-2.5f, -3.2f, -4.5f),
	
	};
	//GLuint indices[] = {
	//	0,1,2,  //tam giac 1
	//	3,2,0    //tam giac 2
	//};
//Lưu trữ VAO,VBO của  đối tượng Lập Phương
	//Bước 2: Khởi tạo VBO, VAO
		//b2.1 VAO
	GLuint VAO_LapPhuong,VAO_Plane;
	glGenVertexArrays(1, &VAO_LapPhuong);
	//bind VAO
	glBindVertexArray(VAO_LapPhuong);
	//b2.2 VBO
	GLuint VBO_LapPhuong,VBO_Plane;


	glGenBuffers(1, &VBO_LapPhuong);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_LapPhuong); // liên kết (bind) VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_DoituongLapPhuong), vertices_DoituongLapPhuong, GL_STATIC_DRAW);

	////b2.3 EBO
	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // liên kết (bind) VBO
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//texture coordinate attribute 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO , cho phép gọi hàm glVertexAttribPointer trong VBO
//unbind VAO
	glBindVertexArray(0);

//Lưu trữ VAO,VBO của  đối tượng Plane
	//Bước 2: Khởi tạo VBO, VAO
		//b2.1 VAO
	
	glGenVertexArrays(1, &VAO_Plane);
	//bind VAO
	glBindVertexArray(VAO_Plane);
	//b2.2 VBO

	glGenBuffers(1, &VBO_Plane);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Plane); // liên kết (bind) VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

	////b2.3 EBO
	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // liên kết (bind) VBO
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//texture coordinate attribute 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO , cho phép gọi hàm glVertexAttribPointer trong VBO
//unbind VAO
	glBindVertexArray(0);



	///Load và tạo 1 texture
	unsigned int Texture_Concrete = loadTexture("thumb_concrete.jpg");

	unsigned int texture_wood = loadTexture("texture_wood2.jpg");


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Game Loop
	while (!glfwWindowShouldClose(window))
	{
		//thời gian mỗi khung hình (per-frame time)
		float currentFrame = glfwGetTime();       //               =0.01        -0                                    =0.011        0.01 
		deltaTime = currentFrame - lastframe;    //deltaTime0 = currentFrame0 - lastframe0;=0.01    //deltaTime1 = currentFrame1 - lastframe1;=0.001
		lastframe = currentFrame;                //lastframe0 = currentFrame0;=0.01                  //lastframe1 = currentFrame1;=0.001

		//input bàn phím 
		processInput(window);
		// check sự kiện  (ấn nút bàn phím, chuột,...)
		glfwPollEvents();
		//Render
		//xóa color buffer
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	


		///xác định ma trận biến đổi (các bạn muốn biến đổi đối tượng như nào )
		glm::mat4 model = glm::mat4(1.0f); // chắc chắn rằng đã tạo ma trận đơn vị
		/*glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);*/

		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));//muốn xoay mô hình đối tượng 1 góc 30 9theo trục x
		//camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		//projection = glm::ortho(0.0f, (float)WIDTH ,0.0f, (float)HEIGHT, 0.1f, 100.0f);
		//lấy vị trị của uniform
		GLuint UniformLocation_model = glGetUniformLocation(ourShader.IDProgram, "model");
		GLuint UniformLocation_view = glGetUniformLocation(ourShader.IDProgram, "view");
		GLuint UniformLocation_projection = glGetUniformLocation(ourShader.IDProgram, "projection");
		//gán giá trị của 3 uniform đến shader

		glUniformMatrix4fv(UniformLocation_view, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(UniformLocation_projection, 1, GL_FALSE, glm::value_ptr(projection));
		//Buoc 3 Vẽ hình
		ourShader.use();
		//bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_wood);
		glBindVertexArray(VAO_LapPhuong);
		            //vẽ chân bàn 1
					model = glm::mat4(1.0f);

					model = glm::translate(model,glm::vec3(5.0f, 50.0f,5.0f) );
					/*float angle = 20.0f * i;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));*/
					glUniformMatrix4fv(UniformLocation_model, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
					//vẽ chân bàn 2
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(95.0f, 50.0f, 5.0f));
					/*float angle = 20.0f * i;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));*/
					glUniformMatrix4fv(UniformLocation_model, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
					//vẽ chân bàn 3
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(5.0f, 50.0f, 195.0f));
					/*float angle = 20.0f * i;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));*/
					glUniformMatrix4fv(UniformLocation_model, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
					//vẽ chân bàn 4
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(95.0f, 50.0f, 195.0f));
					/*float angle = 20.0f * i;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));*/
					glUniformMatrix4fv(UniformLocation_model, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				
		glBindVertexArray(0);






		// Vẽ mặt phẳng Plane 
		glBindVertexArray(VAO_Plane);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture_Concrete);
			model = glm::mat4(1.0f);//đưa vị trí ma trận đổi về vị trí ban đầu (ma trận đơn vị)
			model = glm::translate(model, glm::vec3(50.0f, 100.0f, 100.0f));
			glUniformMatrix4fv(UniformLocation_model, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);

		//	glDeleteBuffers(1, &EBO);


		///swap
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO_LapPhuong);
	glDeleteBuffers(1, &VBO_LapPhuong);





		//Terminate GLFW, xóa và dọn dẹp tài nguyên sau khi thoát
	glfwTerminate();
	return 0;

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	//xử lý sự kiện từ bàn phím mà ấn phím Z
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		chieurong = 2.0f;
		chieudai = 1.0f;
		chieucao = 10.0f;

	}
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

/// <summary>
///  Function "Load Textext"
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
