#include <stdexcept>
#include <algorithm>
#include "stm.hpp"

SymbolTableLayer::SymbolTableLayer() : symbols() {}

bool SymbolTableLayer::insert(const std::string& name, const Symbol& symbol) {
    if (symbols.find(name) != symbols.end()) {
        return false; // Symbol already exists in this layer
    }
    symbols[name] = symbol;
    return true;
}

Symbol* SymbolTableLayer::lookup(const std::string& name) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return &it->second;
    }
    return nullptr;
}

bool SymbolTableLayer::remove(const std::string& name) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        symbols.erase(it);
        return true;
    }
    return false;
}

bool SymbolTableLayer::exists(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

void SymbolTableLayer::clear() {
    symbols.clear();
}

size_t SymbolTableLayer::size() const {
    return symbols.size();
}

// Multi-layered Symbol Table implementation
MultiLayeredSymbolTable::MultiLayeredSymbolTable() : layers() {
    layers.push_back(std::make_unique<SymbolTableLayer>()); // Global layer
}

void MultiLayeredSymbolTable::pushLayer() {
    layers.push_back(std::make_unique<SymbolTableLayer>());
}

void MultiLayeredSymbolTable::popLayer() {
    if (layers.size() <= 1) {
        throw std::runtime_error("Cannot pop the global layer");
    }
    layers.pop_back();
}

bool MultiLayeredSymbolTable::insertInCurrentLayer(const std::string& name, const Symbol& symbol) {
    if (layers.empty()) {
        throw std::runtime_error("No active layer in symbol table");
    }
    return layers.back()->insert(name, symbol);
}

bool MultiLayeredSymbolTable::insertInGlobalLayer(const std::string& name, const Symbol& symbol) {
    if (layers.empty()) {
        throw std::runtime_error("No active layer in symbol table");
    }
    return layers.front()->insert(name, symbol);
}

Symbol* MultiLayeredSymbolTable::lookup(const std::string& name) {
    // Search from innermost layer to outermost layer
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        Symbol* symbol = (*it)->lookup(name);
        if (symbol != nullptr) {
            return symbol;
        }
    }
    return nullptr;
}

Symbol* MultiLayeredSymbolTable::lookupInCurrentLayer(const std::string& name) {
    if (layers.empty()) {
        throw std::runtime_error("No active layer in symbol table");
    }
    return layers.back()->lookup(name);
}

bool MultiLayeredSymbolTable::removeFromCurrentLayer(const std::string& name) {
    if (layers.empty()) {
        throw std::runtime_error("No active layer in symbol table");
    }
    return layers.back()->remove(name);
}

bool MultiLayeredSymbolTable::exists(const std::string& name) const {
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        if ((*it)->exists(name)) {
            return true;
        }
    }
    return false;
}

bool MultiLayeredSymbolTable::existsInCurrentLayer(const std::string& name) const {
    if (layers.empty()) {
        throw std::runtime_error("No active layer in symbol table");
    }
    return layers.back()->exists(name);
}

size_t MultiLayeredSymbolTable::getCurrentLayerDepth() const {
    return layers.size();
}

size_t MultiLayeredSymbolTable::getCurrentLayerSize() const {
    if (layers.empty()) {
        throw std::runtime_error("No active layer in symbol table");
    }
    return layers.back()->size();
}

void MultiLayeredSymbolTable::clearCurrentLayer() {
    if (layers.empty()) {
        throw std::runtime_error("No active layer in symbol table");
    }
    layers.back()->clear();
}

void MultiLayeredSymbolTable::clearAll() {
    layers.clear();
    layers.push_back(std::make_unique<SymbolTableLayer>()); // Reinitialize global layer
}

int MultiLayeredSymbolTable::getLayerOfSymbol(const std::string& name) const {
    for (int i = layers.size() - 1; i >= 0; --i) {
        if (layers[i]->exists(name)) {
            return i;
        }
    }
    return -1; // Symbol not found
}