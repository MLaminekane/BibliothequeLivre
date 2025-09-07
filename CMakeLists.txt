cmake_minimum_required(VERSION 3.20)
project(BibliothequeLivre VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BibliothequeLivre
	main.cpp
	Livre.cpp
	Etudiant.cpp
	Bibliotheque.cpp
)

target_include_directories(BibliothequeLivre PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Affichage récap
message(STATUS "Cible générée: BibliothequeLivre")
