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
		//demander a sam comment sa fonctionne 
		Image(int w, int h, int c, const std::string& m, const unsigned char* buffer) : width(w), height(h), channels(c), model(m) 
		{
			data.resize(height, std::vector<std::vector<unsigned char>>(width, std::vector<undigned char>(xhannels, 0)));
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						data[i][j][k] = buffer[i * width * channels + j * channels + k];
					}
				}
			}
			/*size_t dataSize = w * h * c;
			data.resize(dataSize);
			memcpy(data.data(), buffer, dataSize);*/
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
		//fonction non cont 
		unsigned char& operator()(int i, int j, int k)
		{
			if (i < 0 || i >= width || j < 0 || j >= height || k < 0 || k >= channels)
			{
				throw std::out_of_range("coordonnées hors de l'image");
			}
			return data[i][j][k];
		}

		//fonction cont 
		const unsigned char& operator()(int i, int j, int k) const
		{
			if (i < 0 || i >= width || j < 0 || j >= height || k < 0 || k >= channels)
			{
				throw std::out_of_range("coordonnées hors de l'image");
			}
			return data[i][j][k];
		}

		//les operateurs a ajouter

		//l’accès aux valeurs(via l’opérateur() avec trois paramètres), en deux versions : const et non const
		//operateur const 
		const unsigned char& operator(int i, int j, int k) const
		{
			return data[i][j][k];
		}

		//operateur non const
		unsigned char& operator(int i, int j, int k)
		{
			return data[i][j][k];
		}

		//l’addition avec une autre image(via + et += ) : on additionne les valeurs des pixels correspondants
		//+
		Image operator+(const Image& other) const
		{
			if (width != other.width || height != other.height || channels != other.channels) || model != other.model)
			{
				throw std::invalid_argument("les images ne sont pas compatibles pour une additions")
			}

			Image result(width, height, channels, modell, 0);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) = (*this)(i, j, k) + other(i, j, k);
					}
				}
			}
			return result;

		}

		//+=
		Image operator+=(const Image& other)
		{
			if (width != other.width || height != other.height || channels != other.channels) || model != other.model)
			{
				throw std::invalid_argument("les images ne sont pas compatibles pour une additions")
			}

			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) = (*this)(i, j, k) + other(i, j, k);
					}
				}
			}
			return *this;
		}

		//l’addition avec une valeur(via + et += ) : on additionne la valeur à chaque canal de chaque pixel
		//+
		Image operator+(unsigned char value) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) += value;
					}
				}
			}
			return result;
		}

		//+=
		Image operator+=(unsigned char value)
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) += value;
					}
				}
			}
			return *this;
		}

		//l’addition avec un pixel(tableau de valeurs) (via + et += ) : on additionne les valeurs du pixel a chaque pixel
		//+
		Image operator+(const inigned char* pixel) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) += pixel[k];
					}
				}
			}
			return result;

		}

		//+=
		Image operator+=(const inigned char* pixel)
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) += pixel[k];
					}
				}
			}
			return *this;

		}

		//- la soustraction avec une autre image(via - et -= )
		//-
		Image operator-(const Image& other) const
		{
			if (width != other.width || height != other.height || channels != other.channels) || model != other.model)
			{
				throw std::invali_argument("les images ne sont pas compatibles pour une soustraction")
			}

			Image result(width, height, channels, model, 0);
			
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) = (*this)(i, j, k) - other(i, j, k);
					}
				}
			}
			return result;
		}

		//-=
		Image operator-(const Image& other) 
		{
			if (width != other.width || height != other.height || channels != other.channels) || model != other.model)
			{
				throw std::invali_argument("les images ne sont pas compatibles pour une soustraction")
			}

			Image result(width, height, channels, model, 0);

			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) -= other(i, j, k);
					}
				}
			}
			return *this;
		}

		//- la soustraction avec une valeur(via - et -= )
		//-
		Image operator-(unsigned char value) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) -= value;
					}
				}
			}
			return result;

		}

		//-=
		Image operator-=(unsigned char value)
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) -= value;
					}
				}
			}
			return *this;
		}

		//- la soustraction avec un pixel(via - et -= )
		//-
		Image operator -(const unsigned chat* pixel) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) -= pixel[k];
					}
				}
			}
			return result;
		}

		//-=
		Image operator -=(const unsigned chat* pixel) 
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) -= pixel[k];
					}
				}
			}
			return *this;
		}
		
		//-la différence avec une autre image(via ^ et ^= )
		//^
		Image operator^(const Image& other) const
		{
			if (width != other.width || height != other.height || channels != other.channels) || model != other.model)
			{
				throw std::invali_argument("les images ne sont pas compatibles pour la difference")
			}

			Image result(width, height, channels, model, 0);

			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) = (*this)(i, j, k) ^ other(i, j, k);
					}
				}
			}
			return result;
		}

		//^=
		Image operator^=(const Image& other)
		{
			if (width != other.width || height != other.height || channels != other.channels) || model != other.model)
			{
				throw std::invali_argument("les images ne sont pas compatibles pour la difference")
			}

			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) ^= other(i, j, k);
					}
				}
			}
			return *this;
		}
		
		//- la différence avec une valeur(via ^ et ^= )
		//^
		Image operator^(unsigned char value) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) ^= value;
					}
				}
			}
			return result;

		}

		//^=
		Image operator^=(unsigned char value) const
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) ^= value;
					}
				}
			}
			return *this;

		}
 
		//- la différence avec un pixel(via ^ et ^= )
		//^
		Image operator^(const unsigned char* pixel) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) ^= pixel[k];
					}
				}
			}
			return result;
		}

		//^=
		Image operator^=(const unsigned char* pixel) 
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) ^= pixel[k];
					}
				}
			}
			return *this;
		}
		 

		//- la multiplication par une valeur réelle(via * et *= ) 
		//*
		Image operator*(double value) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) = satic_cast<unsigned char>(result(i, j, k) * value);
					}
				}
			}
			return result;

		}

		//*=
		Image operator*=(double value) 
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) = satic_cast<unsigned char>((*this)(i, j, k) * value);
					}
				}
			}
			return *this;

		}


		// - la division par une valeur réelle (via / et /=)
		//  /
		image operator/(double value) const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) = satic_cast<unsigned char>(result(i, j, k) / value);
					}
				}
			}
			return result;

		}

		// /=
		image operator/=(double value)
		{
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						(*this)(i, j, k) = satic_cast<unsigned char>((*this)(i, j, k) / value);
					}
				}
			}
			return *this;

		}

		/*- le seuillage par une valeur (via <, <=, >, >=, ==, !=) : le résultat sera une image de même taille, avec un
		seul canal en mode “GRAY”, avec les valeurs 0 ou 255*/
		Image operator>=(unsigned char threshold) const
		{
			Image result(width, height, 1, "GRAY", 0);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						if ((*this)(i, j, k) >= threshold)
						{
							result(i, j, 0) = 255;
						}
					}
				}
			}
			return result;

		}

		/* - l’inversement des valeurs (via l’opération unaire ~), le résultat est une image de même taille, ou toutes les
		valeurs sont (255-valeur d’origine)*/
		Image operator~() const
		{
			Image result(*this);
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					for (int k = 0; k < channels; ++k)
					{
						result(i, j, k) = static_cast<unsigned char>(255 - result(i, j, k));
					}
				}
			}
			return result;

		}

		// - l’affichage (via <<) au format “<width>x<height>x<channels> (<mode>)”
		friend std::ostream& operator<<(std::ostream& os, const Image& image)
		{
			os << image.getWidth() << "x" << image.getHeight() << "x" << image.getChannels() << " (" << image.getModel() << ")";
			return os;
		}
	
};


int main() {
	try {
		// Créez une image
		Image image1(3, 3, 3, "RGB", "NONE");

		// Remplissez l'image avec des valeurs arbitraires
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					image1(i, j, k) = i * 10 + j * 3 + k;
				}
			}
		}

		// Affichez l'image
		std::cout << "Image 1: " << image1 << std::endl;

		// Créez une autre image
		Image image2(3, 3, 3, "RGB", "NONE");

		// Remplissez la deuxième image avec d'autres valeurs arbitraires
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					image2(i, j, k) = i * 5 + j * 2 + k;
				}
			}
		}

		// Affichez la deuxième image
		std::cout << "Image 2: " << image2 << std::endl;

		// Effectuez différentes opérations sur les images
		Image sum = image1 + image2;
		std::cout << "Somme des images : " << sum << std::endl;

		Image thresholded = image1 >= 15;
		std::cout << "Image seuillée : " << thresholded << std::endl;

		Image inverted = ~image1;
		std::cout << "Image inversée : " << inverted << std::endl;

		// Testez d'autres opérations ici...

	}
	catch (const std::exception& e) {
		std::cerr << "Erreur : " << e.what() << std::endl;
	}

	return 0;
}



