namespace CommonUtilities
{
	template<typename T>
	class DoubleLinkedList;

	template<typename T>
	class DoubleLinkedListNode
	{
		template<typename T> friend class DoubleLinkedList;
	public:
		DoubleLinkedListNode(T someData)
		{
			myData = someData;
			Next = nullptr;
			Previous = nullptr;
		}
		~DoubleLinkedListNode(){};

		const T& GetData() const
		{
			return myData;
		}

	private:
		T myData;
		DoubleLinkedListNode<T>* Next;
		DoubleLinkedListNode<T>* Previous;
	};
}