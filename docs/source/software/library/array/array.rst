.. _uz_array:

=====
Array
=====

A collection of array data types that are boxed in a ``struct``.
The ``struct`` holds the length of the array such that this can be passed as an argument and received from functions.
The header also provides a makro to determine the size of arrays.

Reference
=========

.. doxygendefine:: UZ_ARRAY_SIZE

.. doxygenstruct:: uz_array_float_t
  :members:

.. doxygenstruct:: uz_array_uint32_t
  :members:

.. doxygenstruct:: uz_array_int32_t
  :members:

.. doxygenstruct:: uz_array_int16_t
  :members:

.. doxygenstruct:: uz_array_uint16_t
  :members:

The structs are typedefed.

Example
=======

Declare an array with data in it, then assign the first element of the array to the ``.data`` struct member.
Pass the array to a function.
Take the `storage duration <https://iso-9899.info/wiki/Storage_Duration>`_ into account when assigning the pointer to ``.data``.


.. code-block:: c

    void examplefunction(void){
        float data[5] = {1.12f, 2.87f, 3.3f, 4.6f, 51.5f};
        uz_array_float_t testarray = {
            .length = UZ_ARRAY_SIZE(data), // ALWAYS use the UZ_ARRAY_SIZE makro in the initialization of the length of the array
            .data = &data[0] // Pointer to the first element of the actual data of the array    
        }; 
        float sum=sum_over_array(testarray); // enables to pass array with length of array
    }

    float sum_over_array(uz_array_float_t array){
        float sum=0.0f;
        for(uint32_t i=0;i<array.length;i++){
            sum+=array.data[i];
        }
        return sum;
    }

.. danger:: If a variable is declared inside of a function and the pointer to this variable (automatic storage duration) is assigned to ``.data``, the ``uz_array`` must not be returned to a calling function.

This leads to buggy code, **do not do this**:

.. code-block:: c

    void fcn(void){
    
    uz_array_float_t var=a_buggy_function(void);
    }

    float a_buggy_function(void){
        float data[5]={1,2,3,4,5};
        uz_array_float_t array{
            .length=UZ_ARRAY_SIZE,
            .data=&data[0]
        };
        return array;
    }