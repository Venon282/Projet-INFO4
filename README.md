# Bird song recognition


This project aims at recognising a bird species by listening to its song on an embedded card equipped with a microphone

## First version

The first version of our model and the conversion of audio into spectrograms and then a training of its images. This is not good because all these transformations are far too resource intensive for embedded boards.


The dataset used is a mixture of two datasets. Each with advantages and disadvantages.

- Dataset 1 : https://www.kaggle.com/datasets/rtatman/british-birdsong-dataset
	- Advantages 
		- Many species
		- Good recording quality
	- Disadvantages
		- 3 songs per species
		- Very different song times

- Dataset 2 : https://www.kaggle.com/datasets/monogenea/birdsongs-from-europe 
	- Advantages 
		- Many species
		- Many sounds
	- Disadvantages
		- Can have differents species in each sounds
		- Very different song times

Number of species : 136
Number of audios : 2352

Parameters : 
![alt text](https://github.com/Venon282/Projet-INFO4/blob/main/Data/Images/Version%201/Parameters.png)

#### With 3 Epocs :

Loss :
![alt text](https://github.com/Venon282/Projet-INFO4/blob/main/Data/Images/Version%201/Loss.png)

Precision :
![alt text](https://github.com/Venon282/Projet-INFO4/blob/main/Data/Images/Version%201/Precision.png)

