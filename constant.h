#ifndef CONSTANT_H
#define CONSTANT_H

#define nullptr NULL

#include <stdlib.h>
#include <string.h>

#define MAX_CONSTANTS 256

#define C_TYPE_NONE     0x00
#define C_TYPE_POINTER  0x80000000

#define C_TYPE_INT      0x01
#define C_TYPE_FLOAT    0x02
#define C_TYPE_CHAR     0x04

namespace G8
{

    typedef size_t C_TYPE;

    template <typename T> struct CONSTANT
    {
        union
        {
            T const *  pVal;
            void *     pBuffer;
        };
        char const *    pName;
        C_TYPE			type;

        CONSTANT(T const * const pVal, char * const pName, C_TYPE const type)
            :pVal(pVal), pName(pName), type(type) {}

        static CONSTANT Empty(void)
        {
            return CONSTANT<T>(nullptr, nullptr, C_TYPE_NONE);
        }

        bool IsEmpty(void)
        {
            return (pVal != nullptr && pName != nullptr && type != C_TYPE_NONE);
        }
    };

    class CONSTANT_SYS
    {
        CONSTANT<void> * pConstants;
        size_t length;

    public:
        CONSTANT_SYS(void)
        {
            // Calculate buffer size
            size_t buffSize = sizeof(CONSTANT<int>) * MAX_CONSTANTS;

            // Create buffer for constants
            pConstants = reinterpret_cast<CONSTANT<void> *>(malloc(buffSize));

            // Zero buffer
            memset(pConstants, 0x00, buffSize);

            // Leave the frst constant empty
            length = 1;
        }

        ~CONSTANT_SYS(void)
        {
            // Free each constant
            for (int i = 0; i < MAX_CONSTANTS; i++)
            {
                free(pConstants[i].pBuffer);
            }

            // Free the constant buffer
            free(pConstants);
            pConstants = nullptr;
        }
    public:
        size_t GetLength(void) const { return length; }

    public:
        /**
        * @brief Finds the index to a CONSTANT
        * @param pName The null terminated name of the CONSTANT
        * @param type  The C_TYPE of CONSTANT, C_TYPE_NONE if unknown
        * @return Returns the index of the first corresponding CONSTANT,
        * or the index to the Empty CONSTANT if no corresponding CONSTANT is found
        */
        size_t Find(char const * const pName, C_TYPE const type = C_TYPE_NONE) const
        {
            for (size_t i = 1; i < length; i++)
            {
                // Check if the types and names match
                if ((pConstants[i].type & type) == type // Type check always passes if type == C_TYPE_NONE
                    && strcmp(pConstants[i].pName, pName) == 0)
                {
                    return i; // We found a match, return the index
                }
            }

            // Return the empty constant
            return 0;
        }

        /**
        * @brief Returns the value of CONSTANT
        *
        * @param index The index of the CONSTANT
        * @requires index < #this.length
        */
        template <typename T> T const GetVal(size_t const index) const
        {
            if (pConstants[index].pVal)
                return *reinterpret_cast<const T*>(pConstants[index].pVal);
            else
                return 0;
        }

        /**
        * @brief Returns the value of a CONSTANT
        * @param pName The name of the CONSTANT
        * @param type  The C_TYPE of CONSTANT, C_TYPE_NONE if unknown
        *
        * @requires pName is not the nullptr, pName is a valid c string
        * @returns GetVal returns the value of the corresponding CONSTANT,
        * or the value of the Empty CONSTANT if no corresponding CONSTANT is found
        */
        template <typename T> T const GetVal(char const * const pName, C_TYPE const type = C_TYPE_NONE) const
        {
            // Find the index of the constant
            int index = Find(pName, type);

            // Return the actual constant
            return GetVal<T>(index);
        }

        /**
        * @brief Adds a constant of type T to the constant buffer
        *
        * @param val   The value to assign to this CONSTANT
        * @param pName The name to give this CONSTANT
        * @param type  The type of this CONSTANT
        *
        * @requires pName is a valid c-string, type != C_TYPE_NONE
        * @returns Add is true iff the CONSTANT is added successfully,
        * otherwise false
        */
        template <typename T> bool Add(char const * const pName, T const val , C_TYPE const type)
        {
            // Check that there is room in the buffer
            if (length >= MAX_CONSTANTS)
                return false;

            // Get next free CONSTANT
            CONSTANT<T> * pNew = reinterpret_cast<CONSTANT<T>*>(pConstants) + length;

            // Total size needed is size of T + size of pName
            size_t size = sizeof(T) + strlen(pName) + 1;

            // Try to malloc the space needed
            T * buffer = reinterpret_cast<T*>(malloc(size));

            if (buffer){ // Create the CONSTANT<T>
                pNew->pBuffer = buffer;
                pNew->pName = reinterpret_cast<char const *>(buffer)+sizeof(T);
                pNew->type = type;
            }
            else{	// failed return false
                return false;
            }

            // Assign the value
            *buffer = val;

            // Calculate the size of pName and copy it to the new space
            size -= sizeof(T);
            memcpy(reinterpret_cast<char *>(buffer)+sizeof(T), pName, size);

            // Everything worked!
            length++;
            return true;
        }

        /**
        * @brief Redefines a CONSTANT
        * @param index The index of the CONSTANT to redefine
        * @param val The new value
        * @requires 0 < index < #this.length
        */
        template <typename T> void Redefine(size_t const index, T const val)
        {
            *(reinterpret_cast<T*>(pConstants[index].pBuffer)) = val;
        }
    };
}

#endif // CONSTANT_H
