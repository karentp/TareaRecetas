#ifndef RECIPEDATABASE
#define RECIPEDATABASE

#include <cstdlib>
#include <iostream>

using namespace std;

struct Node;
struct Recipe;
struct Ingredient;
struct RecipeDataBase;

struct Node {
  Recipe* data;
  Node* next;// puntero para enlazar nodos
  Node(Recipe* d) {
    data = d;
    next = NULL;
  }
};

struct Recipe{

  string recipeName="";
  int recipePortion=0;
  Ingredient* recipeIngredients[20];

  Recipe(string rName,int rPortion){

  	recipeName = rName;
  	recipePortion = rPortion;
    for (int i = 0; i<20 ; i++){
        recipeIngredients[i]=NULL;
    }

  }
  	void printRecipe();
  	void insertIngredient(int);
    bool checkIfExistsIngredient(string);
    int  checkArraySpace();

};

struct Ingredient{
	string ingredientName="";
	int ingredientQuantity=0.0;
	string ingredientMeasureUnit="";

	Ingredient(string iName,int iQuantity,string iMeasureUnit){
		ingredientName= iName;
		ingredientQuantity= iQuantity;
		ingredientMeasureUnit = iMeasureUnit;

	}
	void printIngredient();

};

struct RecipeDataBase{

       Node *headNode, *lastNode;

       RecipeDataBase()
       {
           headNode = lastNode =NULL;
       }

	   void addRecipe(Recipe*);
       Node* lookUpRecipe(string);
       void deleteRecipe(string);
       void printAllRecipes();
       void addIngredient();
	   void deleteIngredient(Recipe*,string);
	   void deleteAtBeginning();
	   void deleteAtEnd();
	   void modifyRecipeName(string,string);
	   void modifyIngredientQuantity(Recipe*,string,int);

};

#endif RECIPEDATABASE

