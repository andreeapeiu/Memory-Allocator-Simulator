**Name: Peiu Andreea**
**Group: 314**

## Segregated Free Lists 1

### Description:

<h2>INIT_HEAP</h2>

        When the program receives this command, it initializes an array of
    lists in which they store **nr_lists** double-chained lists, each block
    having a certain size and address.

<h2>MALLOC 'bytes'</h2>

        This function checks if there is a larger list or
    equal to the parameter received from the stdin to guarantee the possibility
    of allocation of that number of bytes. I retain in **selected_list** and in
    **selected_node** the list and block from which they can allocate. Program
    check whether fragmentation is needed or not.
        If there is already a node of that size, it is moved directly to the 
    list of occupied nodes, otherwise a node of 'bytes' size is allocated. I
    calculate block size I stay and check if there is already a list in the
    array of that size. Flax otherwise, it will be created.

<h2>WRITE</h2>

        The function is responsible for writing data to a dynamically allocated
    memory heap. This function receives as arguments the beginning address of
    the memory area to which it is intended to write, the data to be written,
    the number of bytes to be written, as well as additional information about
    the state of the heap, such as the number of malloc calls, the number of
    free calls, and the number of fragmentations. They are provided to carry
    out the DUMP_MEMORY correctly. 
    Within the function, it is first checked whether the specified address
    exists in the list of occupied nodes. If a node corresponding to the
    address is not found, the function displays an error message and calls the
    **dump_memory()** function to display the current status of the heap, and
    then closes the program. Otherwise, the function starts writing data to the
    allocated memory, ensuring that memory limits are respected and managing
    possible fragmentations or exceptions that may occur during the
    writing process.

<h2>READ</h2>

    Like the WRITE function, it checks if the address received from the stdin
    is valid, and then displays error messages and closes the program or
    displays text, character by character.

<h2>FREE 'address'</h2>

    When the program receives this command, it checks if there is a block
    with this address in the list of occupied nodes that can be deassigned.
    Otherwise, it displays the message "Invalid free". I check if there is
    already a list in the array of that size where I can add the block.
    Otherwise, it will be created.

<h2>DESTROY HEAP</h2>

    This function frees up all program resources and closes it.

<h2>DUMP_MEMORY</h2>

    This command displays all information related to the current status
    of the list array and list of occupied nodes.
 
<h1>Do you think you could have achieved a better implementation?</h1>

        To achieve a better implementation of the theme I could have deleted
    each empty list. This gesture would have been more beneficial for memory
    management and code simplification, as I check every time if *list->size*
    is 0 or not. I also think I could have modulated functions much better and
    reused quite a bit of code.
        In addition, I learned to use generic structures and make casts
    differently than I knew before. I also learned to modularize code into
    multiple .c and .h files.