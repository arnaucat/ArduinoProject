#ifndef Box_h
#define Box_h
class Box
{
    public:
		Box(float  h,float w,float d,float x,float y);
		float getHeigth();
		float getWidth();
		float getDepth();
		float getx();
		float gety();

	private:
		//Aquestes dades son necessaries per a saber quins box poden emmagatzemar quins paquets
		float heigh; //altura del box
		float widt; // amplada del box
		float depth; // profunditat del box
		float x; // Posició horitzontal del box respecte la coordenada 0,0 de la calaixera (a baix a la esquerra)
		float y; // Posició vertical del box .......
};
#endif

