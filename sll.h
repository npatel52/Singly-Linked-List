#ifndef _SLL_H_
#define _SLL_H_
#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>

template<typename E>
class SLL{
 private:
  struct Node;
  Node* head;
  Node* tail;

 public:
 SLL():head(0),tail(0){}; // Constructur : initializes the head and tail with nullptr.
  void prepend(E value); 
  void append(E value);
  inline bool is_empty(Node* node){ return node == 0; };
  void print();
  void insert_at( E data, unsigned int const position );
  E decaudate();
  E decapitate();
  E remove_at( unsigned int const position);
  void clear();
  E item_at_head();
  E item_at_tail();
  E item_at( unsigned int const position );
  bool contains(E const val );
  unsigned int length();
  void removeDuplicates();
  inline bool is_tail(Node* node){ return node == tail; };
  std::string to_string();
  ~SLL();
};

template<typename E>
struct
SLL<E>::Node{
  E data;
  Node* next;
 public:
 Node(E value, Node* next = 0):data( value ), next( next ){}; // Initializing data with value and next with nullptr
};

// --------------------------------------------------------PREPEND-------------------------------------------------
template<typename E>
void
SLL<E>::prepend( E value ){
  // Create a new node that point to head and make head point to that node
  head = new Node(value, head); 
  // If tail points to nullptr, then make it point to a node
  if(is_empty(tail)){
    tail = head;
  }
}

// --------------------------------------------------------APPEND-------------------------------------------------
template<typename E>
void
SLL<E>::append( E value ){

  // If no tail exist
  if(is_empty(tail)){
    prepend( value );
  }else{
    // Create a new node to append it to tail
     tail->next = new Node(value);

    // Update tail to point to last node
    tail = tail->next;
  }
}
//-------------------------------------------------------- decapitate()---------------------------------------------------
template<typename E>
E
SLL<E>::decapitate(){
  E result;
  
  if(is_empty(head)){
    throw std::runtime_error( "Error : decapitate() => No head exist" );
  }else{
    // Store the node after head
    Node* tmp = head->next;

    // Store data
    result = head->data;
    
    // Delete head
    delete head;
    
   // To avoid dangling pointer, update both head and tail 
    if(is_empty(tmp)){
      head = 0;
      tail = 0;
    }else{
      // Update head
      head = tmp;
    }
  }
  
  return result;
}

// --------------------------------------------------------insert_at(pos)-------------------------------------------------
template<typename E>
void
SLL<E>::insert_at( E data, unsigned int const position ){

  // if position is 0, then prepend (so that head and tail are updated (INSERTION AT HEAD)
  if(position == 0){
    prepend( data);
    return;
  }
  
  // Iterate through the linked-list to check for pos
  Node* tmp = head;
  int index = position;
  while(--index){
    // If nullptr is reached, then there is no such position
    if(is_empty(tmp) ){
     throw std::runtime_error("insert_at( data, position) => No such position found");
    }
    tmp = tmp->next;
  }

  // If position is at tail (INSERTION AT TAIL)
  if(is_empty(tmp->next)){
    // append that data
    append( data );
  }
  // (INSERTION IN BETWEEN)
  else{
    // create new node and make it point to the next node
    Node* node = new Node( data, tmp->next);
    
    // make current node point to newly created node
    tmp->next = node;
  }
  
}

//---------------------------------------------------------decaudate()---------------------------------------------------
template<typename E>
E
SLL<E>::decaudate(){

  if(is_empty(head)){
    throw std::runtime_error("decaudate() => No tail found");
  }

  E result;
  
  if(is_tail(head)){
      result = head->data;
      delete head;
      head = 0;
      tail = 0;

  }else{
      Node* node = head;
       
      while(!is_empty(node->next->next)){
	 node = node->next;
      }     
       result = node->next->data;
       Node* tmp = node->next;
       node->next = 0;
       tail = node;
       delete tmp;
    }
    
    return result;
}

//--------------------------------------------------------print()-----------------------------------------------------------
template<typename E>
void
SLL<E>::print(){
  std::cout<<"{ ";
  Node* tmp = head;

  while(!is_empty(tmp)){
    std::cout<< tmp->data;
    tmp = tmp->next;
    if(tmp)
      std::cout<< " => ";
  }
  std::cout<<" }"<<std::endl;

}

// --------------------------------------------------------remove_at(pos)-----------------------------------------------
template<typename E>
E
SLL<E>::remove_at( unsigned int const position){

  E result;
   // CASE 0: if the list is empty
  if(is_empty(head)){
     throw std::runtime_error( " remove_at( position ) => No such position ");
  }

  if(position == 0){
    result = decapitate();
  }else {
  // Iterate through the linked-list to check for pos
  Node* link = head;
  int index = position;
  while(--index){
    // CASE 1: when list reached nullptr and no position is matched 
    if(is_empty(link)){
      throw std::runtime_error( " remove_at( position ) => No such position "); 
    }
    
    link = link->next;
  }

  if(is_empty(link->next)){
    // CASE 2: position is after the last position
    throw std::runtime_error( " remove_at( position ) => No such position "); 
  }
  // (DELETION IN BETWEEN)
  else{

    // If deleting tail 
    if(is_tail(link->next)){
      result = decaudate();
    }else{
    // Store a pointer to the node
    Node* tmp = link->next->next;

    // Store data
    result = link->next->data;
 
    // Delete the node
    delete link->next;

    // make current node point to the node after the deleted node
    link->next = tmp;
  }
 }
  }
  return result;
}
//--------------------------------------------------------Clear()-----------------------------------------------------
template <typename E>
void
SLL<E>::clear(){
  Node* tmp;
  while(!is_empty(head)){
    tmp = head->next;
    delete head;
    head = tmp;
  }
  tail = head;
}

//-------------------------------------------------------item_at_head()----------------------------------------------
template<typename E>
E
SLL<E>::item_at_head(){
  if(is_empty(head)){
    throw std::runtime_error( "ERROR: item_at_head() => No head found");
  }
  return head->data;
}

//-------------------------------------------------------item_at_tail()----------------------------------------------
template<typename E>
E
SLL<E>::item_at_tail(){
  if(is_empty(tail)){
    throw std::runtime_error( "ERROR: item_at_tail() => No tail found");
  }
  return tail->data;
}

//-------------------------------------------------------item_at(pos)----------------------------------------------
template<typename E>
E
SLL<E>::item_at( unsigned int const position ){

  Node* tmp = head;

  if(is_empty(head)){
    throw std::runtime_error( "ERROR: item_at(pos) => No such position found");
  }else{
    int index = position;
    while(index--){
      if(is_empty(tmp->next)){
	 throw std::runtime_error( "ERROR: item_at(pos) => No such position found");
      }
      tmp = tmp->next;
    }
  }
  return tmp->data;
}

//-----------------------------------------------------contains(pos)-----------------------------------------------
template <typename E>
bool
SLL<E>::contains(E const value){
  
  try{
    
    if(item_at_head() == value)
      return true;
    if(item_at_tail() == value)
      return true;
    
    Node* tmp = head->next;
    while(!is_empty(tmp)){\
      // If match found
      if(tmp->data == value)
	return true;
      
      tmp = tmp->next;
    }
  }catch (const std::runtime_error& e){
    return false;
  }

  return false;
}

//---------------------------------------------------------length()---------------------------------------------------
template <typename E>
unsigned int
SLL<E>::length(){
  
  if(is_empty(head)){
    return 0;
  }
  
  int len = 0;
  Node* tmp = head;

  while(!is_empty(tmp)){
    tmp = tmp->next;
    ++len;
  }
  
  return len;
}

//---------------------------------------------------------removeDuplicates-------------------------------------------
template <typename E>
void
SLL<E>::removeDuplicates(){
  // If list is not empty then search for duplicates
  if(!is_empty(head)){

    Node* current = head;
    Node* running;
    Node* previous;
    Node* tmp;
    E value;
    
    while(!is_empty(current)){
      // Value to compare to
      value = current->data;

      previous = current;
      running = current->next;
      
      while(!is_empty(running)){

	if(running->data == value){
	  tmp = previous->next;
	  
	  // Move to next node
	  running = running->next;
	  previous->next = running;

	  // If deleting tail, update tail
	  if(is_tail(tmp))
	    tail = previous;
	  
	  delete tmp;
	}else{
	  previous = running;
	  running = running->next;
	}
	
      }
      
      current = current->next;
    }
  }


}
//---------------------------------------------------------to_string--------------------------------------------------
template <typename E>
std::string
SLL<E>::to_string(){

  std::stringstream ss;  
  ss << "";
  
  if(!is_empty(head)){
    Node* tmp = head;
    
    while(!is_empty(tmp)){
      ss << tmp->data;
      tmp = tmp->next;
    }
  }
  
  return ss.str();
}
// --------------------------------------------------------DESTRUCTOR-------------------------------------------------
template<typename E>
SLL<E>::~SLL(){
  Node* tmp;
  while(!is_empty(head)){
    tmp = head->next;
    delete head;
    head = tmp;
  }
  // Finally head and tail will be automatically deleted as destructor destroy the object
}


#endif
