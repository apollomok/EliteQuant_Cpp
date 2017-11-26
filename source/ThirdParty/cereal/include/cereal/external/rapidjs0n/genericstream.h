// Generic*Stream code from https://code.google.com/p/rapidjs0n/issues/detail?id=20
#ifndef RAPIDJS0N_GENERICSTREAM_H_
#define RAPIDJS0N_GENERICSTREAM_H_

#include "rapidjs0n.h"
#include <iostream>

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable: 4127) // conditional expression is constant
  #pragma warning(disable: 4512) // assignment operator could not be generated
  #pragma warning(disable: 4100) // unreferenced formal parameter
#endif

namespace rapidjs0n {

  //! Wrapper of std::istream for input.
  class GenericReadStream {
    public:
      typedef char Ch;    //!< Character type (byte).

      //! Constructor.
      /*!
        \param is Input stream.
        */
      GenericReadStream(std::istream & is) : is_(&is) {
      }


      Ch Peek() const {
        if(is_->eof()) return '\0';
        return static_cast<char>(is_->peek());
      }

      Ch Take() {
        if(is_->eof()) return '\0';
        return static_cast<char>(is_->get());
      }

      size_t Tell() const {
        return (int)is_->tellg();
      }

      // Not implemented
      void Put(Ch)       { RAPIDJS0N_ASSERT(false); }
      void Flush()       { RAPIDJS0N_ASSERT(false); }
      Ch* PutBegin()     { RAPIDJS0N_ASSERT(false); return 0; }
      size_t PutEnd(Ch*) { RAPIDJS0N_ASSERT(false); return 0; }

      std::istream * is_;
  };


  //! Wrapper of std::ostream for output.
  class GenericWriteStream {
    public:
      typedef char Ch;    //!< Character type. Only support char.

      //! Constructor
      /*!
        \param os Output stream.
        */
      GenericWriteStream(std::ostream& os) : os_(os) {
      }

      void Put(char c) {
        os_.put(c);
      }

      void PutN(char c, size_t n) {
        for (size_t i = 0; i < n; ++i) {
          Put(c);
        }
      }

      void Flush() {
        os_.flush();
      }

      size_t Tell() const {
        return (int)os_.tellp();
      }

      // Not implemented
      char Peek() const    { RAPIDJS0N_ASSERT(false); }
      char Take()          { RAPIDJS0N_ASSERT(false); }
      char* PutBegin()     { RAPIDJS0N_ASSERT(false); return 0; }
      size_t PutEnd(char*) { RAPIDJS0N_ASSERT(false); return 0; }

    private:
      std::ostream& os_;
  };

  template<>
    inline void PutN(GenericWriteStream& stream, char c, size_t n) {
      stream.PutN(c, n);
    }

} // namespace rapidjs0n

// On MSVC, restore warnings state
#ifdef _MSC_VER
    #pragma warning(pop)
#endif
#endif // RAPIDJS0N_GENERICSTREAM_H_
