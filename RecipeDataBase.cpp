#include <cstdlib>
#include <iostream>
#include "RecipeDataBase.h"

using namespace std;

void RecipeDataBase::deleteAtBeginning()
{
	Node * deleted= headNode;
	headNode = headNode->next;
	deleted->next=NULL;
}

void RecipeDataBase::deleteAtEnd()
{
	Node *tmp= headNode;
	while(tmp->next->next!=NULL){
		tmp= tmp->next;
	}
	//Node *current= lastNode; solo si lo voy a retornar
	lastNode=tmp;
	tmp->next=NULL;
}

void RecipeDataBase::addRecipe(Recipe * newRecipe)
{

	if(headNode == NULL)
	{
		headNode= new Node(newRecipe);
		lastNode= headNode;
	}
	else
	{
		Node *newNode= new Node(newRecipe);
		lastNode->next= newNode;
		lastNode = newNode;
	}
}

bool Recipe::checkIfExistsIngredient(string nameIn){
    for (int i = 0; i < 20; i++) {
        if (recipeIngredients[i] != NULL &&
            recipeIngredients[i]->ingredientName == nameIn)
                return true;
        }
    return false;
}


int Recipe::checkArraySpace( ){
    for (int i = 0; i < 20; i++) {
        if (recipeIngredients[i] == NULL) {
            return i;
        }
    }
    return -1;
};

void Recipe::insertIngredient(int position) {
    if (position!=-1)
    {
        string nameIn="";
        int quantityIn=0.0;
        string measureUnit="";

        cout<<"Ingrediente:";
        cin.ignore();
        getline(cin,nameIn);
        bool existsIngredient= checkIfExistsIngredient(nameIn);
        if(!existsIngredient){
            cout<<"Cantidad:";
            cin>>quantityIn;
            cout<<"Unidad de medida: ";
            cin>>measureUnit;
            Ingredient* newIngredient= new Ingredient(nameIn,
                                quantityIn,measureUnit);

            recipeIngredients[position]= newIngredient;
        }
        else cout<<"Ya existe un ingrediente con este nombre"<< endl;

    }else cout<<"No hay espacio para mas ingredientes."<< endl;

}


Node* RecipeDataBase::lookUpRecipe(string name)
{

	Node* temporal= headNode;

	while(temporal!=NULL)
	{
		if(temporal->data->recipeName==name)
		{
			return temporal;
		}
		else
		{
			temporal=temporal->next;
		}
	}
	return temporal;
}


void RecipeDataBase::deleteRecipe(string name)
{
	Node* temporal= headNode;
	if(headNode==NULL) cout<<"No hay recetas en la lista"<<endl;

	//Revisar el primer Nodo en caso de que la lista solo tenga un elemento
	if(temporal->data->recipeName==name) deleteAtBeginning();

	else
	{
		//Si tiene más de un elemento
		while(temporal->next!=NULL)
		{
			if(temporal->next->data->recipeName==name)
			{
				if(temporal->next == lastNode) deleteAtEnd();

				else{
					Node *deleted= temporal->next;
					temporal->next=deleted->next;
					deleted->next= NULL;
				}

			}
			else temporal=temporal->next;
		}
	}
}

void Ingredient::printIngredient()
{
    cout<<"\n\tNombre: "<<ingredientName<<endl;
    cout<<"\tCantidad: "<<ingredientQuantity<<endl;
    cout<<"\tUnidad de Medida: "<<ingredientMeasureUnit<<endl;
}

void Recipe::printRecipe()
{

	cout<<"\nNombre: "<<recipeName<<endl;
	cout<<"Porciones: "<<recipePortion<<endl;
	cout<<"Ingredientes: "<<endl;

	for(int i=0; i<20;i++)
	{
		if (recipeIngredients[i]!=NULL)
            recipeIngredients[i]->printIngredient();
	}

}



void RecipeDataBase::printAllRecipes()
{
	Node* current= headNode;
	unsigned int recipeNumber=0;
	while(current!=NULL)
	{
		recipeNumber++;
		cout<<"----------------------\nReceta #"<<recipeNumber<<endl;
		current->data->printRecipe();
		current=current->next;

	}
}


void RecipeDataBase::modifyRecipeName(string oldName, string newName)
{
    Node* recipeToModify= lookUpRecipe(oldName);
    if(recipeToModify==NULL) cout <<"La receta no existe"<<endl;
    else{
        recipeToModify->data->recipeName= newName;
        cout<<"El nombre fue modificado exitosamente"<<endl;
    }
}


void RecipeDataBase:: modifyIngredientQuantity(Recipe* recipeToModify,
                            string ingredientName,int newQuantity)
{

        for (int i=0; i<20;i++){
            if (recipeToModify->recipeIngredients[i]->ingredientName==ingredientName){
                recipeToModify->recipeIngredients[i]->ingredientQuantity= newQuantity;
                cout<<"La cantidad fue modificada exitosamente"<<endl;
                break;
            }
        }
}


void RecipeDataBase:: deleteIngredient(Recipe* recipeToModify,string ingredientName){

        for (int i=0; i<20;i++){
            if (recipeToModify->recipeIngredients[i]->ingredientName==ingredientName){
                recipeToModify->recipeIngredients[i]=NULL;
                cout<<"El ingrediente fue eliminado exitosamente"<<endl;
                break;
            }
        }

}



