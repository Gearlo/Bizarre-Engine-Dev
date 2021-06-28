/* 
 * File:   BList.h
 * Author: ariel
 *
 * Created on 02 de junio de 2017, 09:23 PM
 */



#ifndef BList_H
#define BList_H

#include <iostream>

/*
    -Crear un crear and destroy objetos ¿ya está?
    -Crear operadores para concatenar listas
    -Poder inicializar la lista en el constructor
*/

template <class L> class BList{
    private:
        template <class C> class BList_Cell{
            public:
                C data;
                BList_Cell<C> * next; // apuntador a la siguiente celda
                
                BList_Cell(void){ data = NULL; next = NULL; } //contructor
                //BList_Cell(void){ next = NULL; } //contructor
                BList_Cell(C data){ this->data = data; next = NULL;  } // constructor
                ~BList_Cell(void){};  // destructor
            
                void eraseAll(void){ if(next){ next->eraseAll(); } ; delete(next); next = NULL; }
                void eraseAndDestroyAll(void){ if(!next){ next->eraseAndDestroyAll(); } ; delete(data); delete(next); }
        };
        
        private:
            BList_Cell<L> *root, *last, *before, *current;
        
        public:
            BList(void){ before = root = last = current = new BList_Cell<L>(); }; //constructor
            ~BList(void){ if(!isEmpty()){ clear(); } } //destructor
            
            inline void append(L data){
                last->next = new BList_Cell<L>(data);  
                last = last->next;        
            }
            
            inline void append( BList<L>* list ){
                list->restart();
                L data = list->next();
                while(data){
                    append(data);
                    data = list->next();
                }    
            }
            
            inline void clear(void){ root->eraseAll() ; last = current = root;  }
            inline void clearAndDestroyObject(void){ root->eraseAndDestroyAll() ; last = current = root;  }
            
            
            L& operator[](unsigned int i){
                return get(i);
            }
            
            L operator[](unsigned int i) const {
                return get(i);
            }
            
            /**
            * get any item from the list.
            *
            * @param index, Item position.
            * @return value 
            */
            inline L get(unsigned int index){
                restart();
                int i = 0;
                L element =  next();
                while(i < index){
                    element =  next(); i++;
                }
                return element;
            }
            
            
            inline L next(void) {
                //std::cout <<(current == NULL ) << std::endl;
                if(current->next){ 
                    before = current; 
                    current = current->next; 
                    return current->data;
                }else{ return NULL;} 
            };
            
            inline L getCurrent(void){
                return current->data;
            };
            
            void removeCurrent(void){
                //std::cout << "before " << before->data << "| current " << current->data << std::endl;
                BList_Cell<L>* tmp = current;
                
                if( current->next ){
                    before->next = current->next;
                    current = before;
                }else{
                    last = before;
                    before->next = NULL;
                    current = before;
                }
                
            }
            
            
            inline void restart(void){ current = root; };
            
            
            bool isEmpty(void){
                ///metodo que retorna "true" en caso de que la lista no tenga ningun elemento
                if(this->root->next){
                    return false;
                }else{
                    return true;
                }
            }
            
            unsigned int leght(void){
                ///metodo que devuelve la logintud total de la lista tomando al cero como primera posicion
                int returnLeght = 0;
                BList_Cell<L>* tmp = this->root->next;
                while(tmp){
                    returnLeght++;
                    tmp = tmp->next;
                }
                return returnLeght;
            }
            
            BList<L>* clone(void){
                BList<L>* newList = new BList<L>();
                this->restart();
                L element= this->next();
                while(element){
                    newList->append(element);
                    element= this->next();
                }
                return newList;
            }
                     
};

#endif /* BLIST_H */

