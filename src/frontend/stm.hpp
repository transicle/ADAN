#ifndef STM
#define STM

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

struct Symbol {
    std::string name;
    std::string type;
    int scope_level;
};

class SymbolTableLayer {
public:
    SymbolTableLayer();

    bool insert(const std::string& name, const Symbol& symbol);
    Symbol* lookup(const std::string& name);
    bool remove(const std::string& name);
    bool exists(const std::string& name) const;
    void clear();
    size_t size() const;

private:
    std::unordered_map<std::string, Symbol> symbols;
};

class MultiLayeredSymbolTable {
public:
    MultiLayeredSymbolTable();

    void pushLayer();
    void popLayer();

    bool insertInCurrentLayer(const std::string& name, const Symbol& symbol);
    bool insertInGlobalLayer(const std::string& name, const Symbol& symbol);

    Symbol* lookup(const std::string& name);
    Symbol* lookupInCurrentLayer(const std::string& name);

    bool removeFromCurrentLayer(const std::string& name);

    bool exists(const std::string& name) const;
    bool existsInCurrentLayer(const std::string& name) const;

    size_t getCurrentLayerDepth() const;
    size_t getCurrentLayerSize() const;

    void clearCurrentLayer();
    void clearAll();

    int getLayerOfSymbol(const std::string& name) const;

private:
    std::vector<std::unique_ptr<SymbolTableLayer>> layers;
};

#endif // STM