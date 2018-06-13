#ifndef LINEEDIT_H
#define LINEEDIT_H

template<class Container, class Type = typename Container::value_type>
class line_editor {
	Container container;
	typename Container::iterator cursor;
	bool insert_mode;
	
public:
	line_editor() : cursor(container.begin()), insert_mode(true) {}

	void press(const Type& elem) {
		if(insert_mode || cursor == container.end()) {
			cursor = ++container.insert(cursor, elem);
		} else {
			*cursor++ = elem;
		}
	}
	
	void home() {
		cursor = container.begin();
	}
	
	Container enter() {
		Container result;
		std::swap(result, container);
		home();
		return result;
	}
	
	void insert() {
		insert_mode = !insert_mode;
	}
	
	void del() {
		if(cursor == container.end()) return;
		
		cursor = container.erase(cursor);
	}
	
	void backspace() {
		if(cursor == container.begin()) return;
		
		--cursor;
		del();
	}
	
	template<class OtherContainer, class OtherType>
	friend class line_editor;
	
	template<class OtherContainer>
	void swap(line_editor<OtherContainer, Type>& other) {
		std::pair<int, Container> savedData = getData();
		setData(other.getData());
		other.setData(savedData);
		
		std::swap(insert_mode, other.insert_mode);
	}
	
private:
	std::pair<int, Container> getData() {
		int cursorPos = std::distance(container.begin(), cursor);
		return std::make_pair(cursorPos, enter());
	}
	
	template<class OtherContainer>
	void setData(const std::pair<int, OtherContainer>& data) {
		container.assign(data.second.begin(), data.second.end());
		home();
		std::advance(cursor, data.first);
	}
	
	line_editor(const line_editor&);
};

#endif // LINEEDIT_H
