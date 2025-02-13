class Symbol:
    """A class representing a symbol in the symbol table."""
    def __init__(self, name, type_, scope):
        self.name = name       # Identifier name
        self.type_ = type_     # Data type (e.g., int, float, string)
        self.scope = scope     # Scope level
        self.next = None       # Pointer to the next symbol (for linked list)

class SymbolTable:
    """Symbol Table implemented using a linked list."""
    def __init__(self):
        self.head = None  # Head of the linked list

    def insert(self, name, type_, scope):
        """Insert a new symbol at the beginning of the linked list."""
        if self.lookup(name, scope):
            print(f"Error: '{name}' already declared in scope {scope}.")
            return
        new_symbol = Symbol(name, type_, scope)
        new_symbol.next = self.head
        self.head = new_symbol

    def lookup(self, name, scope):
        """Search for a symbol in the table (current or parent scope)."""
        temp = self.head
        while temp:
            if temp.name == name and temp.scope == scope:
                return temp  # Symbol found
            temp = temp.next
        return None  # Symbol not found

    def modify(self, name, type_, scope):
        """Modify the type of an existing symbol."""
        symbol = self.lookup(name, scope)
        if symbol:
            symbol.type_ = type_
        else:
            print(f"Error: Symbol '{name}' not found in scope {scope}.")

    def delete(self, name, scope):
        """Delete a symbol from the table."""
        temp = self.head
        prev = None
        while temp:
            if temp.name == name and temp.scope == scope:
                if prev:
                    prev.next = temp.next
                else:
                    self.head = temp.next
                return
            prev = temp
            temp = temp.next
        print(f"Error: Symbol '{name}' not found in scope {scope}.")

    def display(self):
        """Display all symbols in the symbol table."""
        temp = self.head
        print("\nSymbol Table:")
        print("Name\tType\tScope")
        print("----------------------")
        while temp:
            print(f"{temp.name}\t{temp.type_}\t{temp.scope}")
            temp = temp.next
        print()

