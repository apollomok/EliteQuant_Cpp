#ifndef RAPIDJS0N_STRINGBUFFER_H_
#define RAPIDJS0N_STRINGBUFFER_H_

#include "rapidjs0n.h"
#include "internal/stack.h"

namespace rapidjs0n {

//! Represents an in-memory output stream.
/*!
	\tparam Encoding Encoding of the stream.
	\tparam Allocator type for allocating memory buffer.
	\implements Stream
*/
template <typename Encoding, typename Allocator = CrtAllocator>
struct GenericStringBuffer {
	typedef typename Encoding::Ch Ch;

	GenericStringBuffer(Allocator* allocator = 0, size_t capacity = kDefaultCapacity) : stack_(allocator, capacity) {}

	void Put(Ch c) { *stack_.template Push<Ch>() = c; }

	void Clear() { stack_.Clear(); }

	const char* GetString() const {
		// Push and pop a null terminator. This is safe.
		*stack_.template Push<Ch>() = '\0';
		stack_.template Pop<Ch>(1);

		return stack_.template Bottom<Ch>();
	}

	size_t Size() const { return stack_.GetSize(); }

	static const size_t kDefaultCapacity = 256;
	mutable internal::Stack<Allocator> stack_;
};

typedef GenericStringBuffer<UTF8<> > StringBuffer;

//! Implement specialized version of PutN() with memset() for better performance.
template<>
inline void PutN(GenericStringBuffer<UTF8<> >& stream, char c, size_t n) {
	memset(stream.stack_.Push<char>(n), c, n * sizeof(c));
}

} // namespace rapidjs0n

#endif // RAPIDJS0N_STRINGBUFFER_H_
