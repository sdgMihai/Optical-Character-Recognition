// Copyright (C) 2018 Trasca Andrei si Gheoace Mihai - All Rights Reserved

Optical Character recognition(Tema 3)
	Simplified version of Random Forest algorithm. It has two phases, a learning phase
	when the forests are being made, feeding the project with samples and a second one,
	predicting the value represented by the picture. The purpose of the program is
	to successfully detect the letter represented by the image(0-9).
	

	Trasca Andrei implemented(alone):
	- get_random_samples() from randomForest.cpp
	- same_class() from decisionTree.cpp
	- compute_unique() from decisionTree.cpp
	- get_split_as_indexes() from decisionTree.cpp
	- random_dimensions() from decisionTree.cpp
	Gheoace Mihai implemented(alone):
	- get_entropy_by_indexes() from decisionTree.cpp
	- find_best_split() from decisionTree.cpp
	- Node::predict() from decisionTree.cpp
	- Node::make_leaf() from decisionTree.cpp
	- Node::train() from decisionTree.cpp
	The last 5 tasks had some seg-faults we've solved toghether.
	
	
