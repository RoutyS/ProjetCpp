#include <iostream>
#include <string>
#include <cstring>
#include <vector>


class Image
{
	private:

		int width;
		int height;
		int channels;
		std::string model;
		std::string rempVal;
		std::vector<unsigned char> data;

	public:	
	
	//constructeur par défaut, mettant les trois dimensions a 0, et le modèle à “NONE”
		Image() : width(0), height(0), channels(0),model("NONE"){}

	//constructeur avec les trois dimensions, le modèle, et une valeur de remplissage
		Image(int w, int h, int c, const std::string& m, const std::string& remp) : width(w), height(h), channels(c), model(m), rempVal(remp){}

	//constructeur avec les trois dimensions, le modèle, et un buffer à recopier
		Image(int w, int h, int c, const std::string& m, const unsigned char* buffer) : width(w), height(h), channels(c), model(m) 
		{
			size_t dataSize = w * h * c;
			data.resize(dataSize);
			memcpy(data.data(), buffer, dataSize);
		}

	// tout ce qu’il faut pour compléter la règle des 3

	// les getters et setters des attributs

//methode get
		
		int getWidth() const
		{
			return width;
		}

		int getHeight() const 
		{
			return height;
		}

		int getChannels() const
		{
			return channels;
		}

		std::string getModel() const
		{
			return model;
		}

		//methode set

		void setWidth(int w)
		{
			width = w;
		}

		void setHeight(int h)
		{
			height = h;
		}

		void setChannels(int c)
		{
			channels = c;
		}

		void setModel(const std::string& m)
		{
			model = m;
		}
	/*deux fonctions at (const et non const), prenant 3 coordonné es, pour accé der à une valeur. Si les
	coordonnées sont en dehors de l’image, on lancera une exception
	*/
		//operateur () pour acceder aux valeurs de l'image en fonction 

		unsigned char& operator()(int x, int y, int channel)
		{
			if (x < 0 || x >= width || y < 0 || y >= height || channel < 0 || channel >= channels)
			{
				throw std::out_of_range("Coordonnées hors de l'image");
			}
			return data[(y * width + x) * channels + channel];
		}

		//operateur () en version const pour acceder aux valeurs de l'image

		const unsigned char& operator()(int x, int y, int channel) const
		{
			if (x < 0 || x >= width || y < 0 || y >= height || channel < 0 || channel >= channels)
				{
				throw std::out_of_range("Coordonnées hors de l'image");
				}
			return data[(y * width + x) * channels + channel];
		}

		//operateur d'addition avec une autre image 
		Image operator+(const Image& other) const
		{
			if (width != other.width || height != other.height || channels != other.channels || model != other.model)
			{
				throw std::invalid_argument("Les images ne sont pas compatibles pour l'addition.");
			}
			Image result(width, height, channels, model, rempVal);

			for (int i = 0; i < data.size(); ++i)
			{
				result.data[i] = data[i] + other.data[i];
			}
			return result;
		}

		//operateur d'addition avec une valeur
		Image operator+(unsigned char value) const 
		{
			Image result(*this);
			for (int i = 0; i < result.data.size(); ++i)
			{
				result.data[i] += value;
			}
			return result;

		}

		//fonction pour effectuer l'operation d'inversion

		Image inverse() const
		{
			Image result(*this);
			for (int i = 0; i < result.data.size();++i)
			{
				result.data[i] = 255 - result.data[i];
			}
			return result;
		}

		//fonction pour effectuer le seullage par valeur 
		Image seuillage(unsigned char seuillageValue) const
		{
			Image result(width, height, 1, "GRAY", rempVal);
			for (int i = 0; i < data.size(); ++i)
			{
				result.data[i] = (data[i] < seuillageValue) ? 0 : 255;
			}
			return result;
		}

		//operateur d'affihage
		friend std::ostream& operator<<(std::ostream& os, const Image& image)
		{
			os << image.width << "x" << image.height << "x" << image.channels << " (" << image.model << ")";
			return os;
		}
		



	
};

int main()
{
	//exemple de donnees
	unsigned char buffer[] = { 255, 0, 0, 0, 255, 0, 0, 0, 255 };

	//cree une image personnalisee a partir du buffer
	Image customImage(3, 3, 3, "RGB", buffer);

	//afficher les informations de l image
	//customImage.displayInfo();

	return 0;
}

//les operateurs a ajouter

//- l’accès aux valeurs (via l’opérateur () avec trois paramètres), en deux versions : const et non const

// - l’addition avec une autre image (via + et +=) : on additionne les valeurs des pixels correspondants

//- l’addition avec une valeur (via + et +=): on additionne la valeur à chaque canal de chaque pixel

// l’addition avec un pixel (tableau de valeurs) (via + et +=) : on additionne les valeurs du pixel a chaque pixel

//la soustraction avec une autre image (via - et -=) 

//- la soustraction avec une valeur(via - et -=) 

//- la soustraction avec un pixel (via - et -=) 

// - la différence avec une autre image (via ^ et ^=) 

// - la différence avec une valeur (via ^ et ^=)

//- la différence avec un pixel (via ^ et ^=)

//- la multiplication par une valeur réelle (via * et *=)

// - la division par une valeur réelle (via / et /=)

/*- le seuillage par une valeur (via <, <=, >, >=, ==, !=) : le résultat sera une image de même taille, avec un
seul canal en mode “GRAY”, avec les valeurs 0 ou 255*/

/* - l’inversement des valeurs (via l’opération unaire ~), le résultat est une image de même taille, ou toutes les
valeurs sont (255-valeur d’origine)*/

// - l’affichage (via <<) au format “<width>x<height>x<channels> (<mode>)”
