#version 330 core

in vec3 ourColor;//��ɫ����
in vec2 TexCoord;//��������

out vec4 FragColor;//ƬԪ��ɫ���

//uniform sampler2D ourTexture;//samplerָ�����������ڽ�������ӵ�Ƭ����ɫ����

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//texture()�������ڲ���������ɫ��
	//��һ��������������������ڶ����Ƕ�Ӧ���������ꣻ
	//����ʹ��֮ǰ���õ������������Ӧ����ɫֵ���в�����ʹƬ����ɫ��������������ֵ��������ɫ

	//FragColor = texture(ourTexture, TexCoord);//��������
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);//��������ɫ�Ļ��
	
	/*mix()��������������Ϊ��������ɫ�����Բ�ֵ(0-1֮�䣬0��ʾֻ�е�һ�ֲ��ʣ�1��ʾֻ�еڶ��ֲ���)*/
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);//���������Ļ��
}