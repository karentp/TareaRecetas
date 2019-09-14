#include <iostream>
#include "RecipeDataBase.h"

using namespace std;

int opcion;
void menu();

string getRecipeName(){
    string name="";
    cout<<"\nNombre de la Receta:";
    cin.ignore();
    getline(cin,name);
    return name;
}

int main()
{
    cout <<"Base de Datos de Recetas\n"<<endl;
    RecipeDataBase* newDataBase= new RecipeDataBase();
    //Agregar recetas
    Recipe* newRecipe= new Recipe("Arroz con leche",5);
    newRecipe->recipeIngredients[0]= new Ingredient("arroz",3,"tazas");
    newRecipe->recipeIngredients[1]= new Ingredient("agua",1,"l");
    newRecipe->recipeIngredients[2]= new Ingredient("leche",2,"l");
    newDataBase->addRecipe(newRecipe);

    Recipe* newRecipe2= new Recipe("Pollo",4);
    newRecipe2->recipeIngredients[0]= new Ingredient("pechuga",1,"kg");
    newRecipe2->recipeIngredients[1]= new Ingredient("salsa blanca",10,"ml");
    newRecipe2->recipeIngredients[2]= new Ingredient("hongos",1,"caja");
    newDataBase->addRecipe(newRecipe2);

    Recipe* newRecipe3= new Recipe("Lasana",6);
    newRecipe3->recipeIngredients[0]= new Ingredient("pasta",3,"paquetes");
    newRecipe3->recipeIngredients[1]= new Ingredient("pollo",1,"kg");
    newRecipe3->recipeIngredients[2]= new Ingredient("sal",1,"g");
    newDataBase->addRecipe(newRecipe3);

    Recipe* newRecipe4= new Recipe("Helado de fresa",4);
    newRecipe4->recipeIngredients[0]= new Ingredient("fresas",500,"g");
    newRecipe4->recipeIngredients[1]= new Ingredient("yogurt",1,"l");
    newRecipe4->recipeIngredients[2]= new Ingredient("leche",2,"l");
    newRecipe4->recipeIngredients[3]= new Ingredient("azucar",10,"g");
    newDataBase->addRecipe(newRecipe4);


    do{

        menu();
        switch(opcion){
            case 1:
            {
                string name=getRecipeName();
                int portions=0.0;
                Node * repited= newDataBase->lookUpRecipe(name);
                if (repited==NULL || newDataBase->headNode ==NULL){
                    cout<<"Cantidad de Porciones:";
                    cin>>portions;
                    Recipe* newRecipe= new Recipe(name,portions);
                    int opcionIng;
                    do{
                        int position= newRecipe->checkArraySpace();
                        newRecipe->insertIngredient(position);
                        cout<<"\n1. Ingresar otro ingrediente\n"<<
                        "2. Ingresar receta\nOpcion:";
                        cin>>opcionIng;
                    }
                    while(opcionIng==1);

                    newDataBase->addRecipe(newRecipe);
                }else
                    cout <<"\nYa existe una receta con este nombre"<<endl;

                break;
            }
            case 2:{
                string name=getRecipeName();
                Node* recipe=newDataBase->lookUpRecipe(name);
                if (recipe!=NULL)
                    recipe->data->printRecipe();
                else
                    cout<<"\nLa receta no se encontro"<<endl;
                break;
            }
            case 3:{
                string name=getRecipeName();
                Node* recipe=newDataBase->lookUpRecipe(name);
                if (recipe!=NULL)
                    newDataBase->deleteRecipe(name);
                else cout<<"La receta no existe"<<endl;
                break;
            }
            case 4:
                newDataBase->printAllRecipes();
                break;

            case 5:{
                string oldName=getRecipeName();
                string newName="";
                cout<<"Nombre nuevo para la Receta:";
                getline(cin,newName);
                newDataBase->modifyRecipeName(oldName,newName);
                break;

            }
            case 6:{
                string recipeName=getRecipeName();
                string ingredientName="";
                int newQuantity=0;
                Node* recipeToModify= newDataBase->lookUpRecipe(recipeName);
                if(recipeToModify==NULL) cout <<"La receta no existe"<<endl;
                else{
                    cout<<"Nombre del Ingrediente:";
                    getline(cin,ingredientName);

                    if(!recipeToModify->data->checkIfExistsIngredient(ingredientName))
                        cout <<"\nEl ingrediente no existe en esta receta"<<endl;
                    else{
                        cout<<"Cantidad nueva:";
                        cin>>newQuantity;
                        newDataBase->modifyIngredientQuantity(recipeToModify->data,ingredientName,newQuantity);
                    }
                }
                    break;
            }
            case 7:{
                string recipeName=getRecipeName();
                Node* recipe=newDataBase->lookUpRecipe(recipeName);
                if(recipe==NULL) cout <<"La receta no existe"<<endl;
                else{
                    int position= recipe->data->checkArraySpace();
                    recipe->data->insertIngredient(position);
                }
                break;
            }
            case 8:{
                string recipeName=getRecipeName();
                string ingredientName="";
                Node* recipe=newDataBase->lookUpRecipe(recipeName);
                if(recipe==NULL) cout <<"La receta no existe"<<endl;
                else{
                    cout<<"Nombre del Ingrediente:";
                    getline(cin,ingredientName);
                    if(!recipe->data->checkIfExistsIngredient(ingredientName))
                        cout <<"\nEl ingrediente no existe en esta receta"<<endl;
                    else
                        newDataBase->deleteIngredient(recipe->data,ingredientName);
                }
                break;
            }
            default:

                break;

        }
    } while(opcion!=9);


    return 0;
}


void menu(){
    cout<<"\nMenu:\n\n 1. Agregar receta\n"<<
    "2. Buscar Receta\n"<<"3. Borrar receta\n"<<
    "4. Imprimir todas las recetas\n"<<"5. Modificar nombre de una receta\n"<<
    "6. Modificar cantidad de un ingrediente de una receta\n"<<
    "7. Agregar ingrediente a una receta\n"<<"8. Borrar ingrediente\n"<<
    "9. Salir.\n"<<endl;
    cout<<"Ingrese el numero de la opcion:";
    cin >>opcion;
}
