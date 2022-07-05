#include "souffle/CompiledSouffle.h"
#include "souffle/SignalHandler.h"
#include "souffle/SouffleInterface.h"
#include "souffle/datastructure/BTree.h"
#include "souffle/io/IOSystem.h"
#include <any>
namespace functors {
extern "C" {
}
} //namespace functors
namespace souffle::t_btree_ii__0_1__11__10 {
struct Type {
static constexpr Relation::arity_type Arity = 2;
using t_tuple = Tuple<RamDomain, 2>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :(0));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11__10 
namespace souffle::t_btree_ii__0_1__11__10 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[2];
std::copy(ramDomain, ramDomain + 2, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1) {
RamDomain data[2] = {a0,a1};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_11(lower,upper,h);
}
range<t_ind_0::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_10(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [0,1]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_ii__0_1__11__10 
namespace souffle::t_btree_ii__0_1__11 {
struct Type {
static constexpr Relation::arity_type Arity = 2;
using t_tuple = Tuple<RamDomain, 2>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :(0));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11 
namespace souffle::t_btree_ii__0_1__11 {
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[2];
std::copy(ramDomain, ramDomain + 2, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1) {
RamDomain data[2] = {a0,a1};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_11(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [0,1]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_ii__0_1__11 
namespace souffle {
class Stratum_negrel_645397d4433f2251 {
public:
 Stratum_negrel_645397d4433f2251(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_negrel_104f7d9aa50fc028,t_btree_ii__0_1__11__10::Type& rel_rel_46957df9a921aa76);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_ii__0_1__11::Type* rel_negrel_104f7d9aa50fc028;
t_btree_ii__0_1__11__10::Type* rel_rel_46957df9a921aa76;
};
} // namespace souffle
namespace souffle {
 Stratum_negrel_645397d4433f2251::Stratum_negrel_645397d4433f2251(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_negrel_104f7d9aa50fc028,t_btree_ii__0_1__11__10::Type& rel_rel_46957df9a921aa76):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_negrel_104f7d9aa50fc028(&rel_negrel_104f7d9aa50fc028),
rel_rel_46957df9a921aa76(&rel_rel_46957df9a921aa76){
}

void Stratum_negrel_645397d4433f2251::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(negrel(x,y) :- 
   rel(x,z),
   rel(z,y),
   !rel(x,y),
   x != y.
in file hello.dl [8:1-8:58])_");
if(!(rel_rel_46957df9a921aa76->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_negrel_104f7d9aa50fc028_op_ctxt,rel_negrel_104f7d9aa50fc028->createContext());
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
for(const auto& env0 : *rel_rel_46957df9a921aa76) {
auto range = rel_rel_46957df9a921aa76->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1])) && !(rel_rel_46957df9a921aa76->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env1[1])}};
rel_negrel_104f7d9aa50fc028->insert(tuple,READ_OP_CONTEXT(rel_negrel_104f7d9aa50fc028_op_ctxt));
}
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","negrel"},{"operation","output"},{"output-dir","."},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_negrel_104f7d9aa50fc028);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (pruneImdtRels) rel_rel_46957df9a921aa76->purge();
}

} // namespace souffle

namespace souffle {
class Stratum_rel_2fae15197198755a {
public:
 Stratum_rel_2fae15197198755a(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_delta_rel_01f91f5adec19d96,t_btree_ii__0_1__11::Type& rel_new_rel_18cf54c1996edfc3,t_btree_ii__0_1__11__10::Type& rel_rel_46957df9a921aa76);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_ii__0_1__11::Type* rel_delta_rel_01f91f5adec19d96;
t_btree_ii__0_1__11::Type* rel_new_rel_18cf54c1996edfc3;
t_btree_ii__0_1__11__10::Type* rel_rel_46957df9a921aa76;
};
} // namespace souffle
namespace souffle {
 Stratum_rel_2fae15197198755a::Stratum_rel_2fae15197198755a(SymbolTable& symTable,RecordTable& recordTable,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_delta_rel_01f91f5adec19d96,t_btree_ii__0_1__11::Type& rel_new_rel_18cf54c1996edfc3,t_btree_ii__0_1__11__10::Type& rel_rel_46957df9a921aa76):
symTable(symTable),
recordTable(recordTable),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_delta_rel_01f91f5adec19d96(&rel_delta_rel_01f91f5adec19d96),
rel_new_rel_18cf54c1996edfc3(&rel_new_rel_18cf54c1996edfc3),
rel_rel_46957df9a921aa76(&rel_rel_46957df9a921aa76){
}

void Stratum_rel_2fae15197198755a::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
signalHandler->setMsg(R"_(rel(1,2).
in file hello.dl [2:1-2:11])_");
[&](){
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(1)),ramBitCast(RamSigned(2))}};
rel_rel_46957df9a921aa76->insert(tuple,READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt));
}
();signalHandler->setMsg(R"_(rel(1,3).
in file hello.dl [3:1-3:11])_");
[&](){
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(1)),ramBitCast(RamSigned(3))}};
rel_rel_46957df9a921aa76->insert(tuple,READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt));
}
();signalHandler->setMsg(R"_(rel(4,5).
in file hello.dl [4:1-4:11])_");
[&](){
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(4)),ramBitCast(RamSigned(5))}};
rel_rel_46957df9a921aa76->insert(tuple,READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt));
}
();signalHandler->setMsg(R"_(rel(1,5).
in file hello.dl [5:1-5:11])_");
[&](){
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
Tuple<RamDomain,2> tuple{{ramBitCast(RamSigned(1)),ramBitCast(RamSigned(5))}};
rel_rel_46957df9a921aa76->insert(tuple,READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt));
}
();[&](){
CREATE_OP_CONTEXT(rel_delta_rel_01f91f5adec19d96_op_ctxt,rel_delta_rel_01f91f5adec19d96->createContext());
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
for(const auto& env0 : *rel_rel_46957df9a921aa76) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_delta_rel_01f91f5adec19d96->insert(tuple,READ_OP_CONTEXT(rel_delta_rel_01f91f5adec19d96_op_ctxt));
}
}
();iter = 0;
for(;;) {
signalHandler->setMsg(R"_(rel(x,y) :- 
   rel(y,x).
in file hello.dl [6:1-6:24])_");
if(!(rel_delta_rel_01f91f5adec19d96->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_delta_rel_01f91f5adec19d96_op_ctxt,rel_delta_rel_01f91f5adec19d96->createContext());
CREATE_OP_CONTEXT(rel_new_rel_18cf54c1996edfc3_op_ctxt,rel_new_rel_18cf54c1996edfc3->createContext());
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
for(const auto& env0 : *rel_delta_rel_01f91f5adec19d96) {
if( !(rel_rel_46957df9a921aa76->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[1]),ramBitCast(env0[0])}};
rel_new_rel_18cf54c1996edfc3->insert(tuple,READ_OP_CONTEXT(rel_new_rel_18cf54c1996edfc3_op_ctxt));
}
}
}
();}
if(rel_new_rel_18cf54c1996edfc3->empty()) break;
[&](){
CREATE_OP_CONTEXT(rel_new_rel_18cf54c1996edfc3_op_ctxt,rel_new_rel_18cf54c1996edfc3->createContext());
CREATE_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt,rel_rel_46957df9a921aa76->createContext());
for(const auto& env0 : *rel_new_rel_18cf54c1996edfc3) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_rel_46957df9a921aa76->insert(tuple,READ_OP_CONTEXT(rel_rel_46957df9a921aa76_op_ctxt));
}
}
();std::swap(rel_delta_rel_01f91f5adec19d96, rel_new_rel_18cf54c1996edfc3);
rel_new_rel_18cf54c1996edfc3->purge();
iter++;
}
iter = 0;
rel_delta_rel_01f91f5adec19d96->purge();
rel_new_rel_18cf54c1996edfc3->purge();
}

} // namespace souffle

namespace souffle {
class Sf_hello: public SouffleProgram {
public:
 Sf_hello();
 ~Sf_hello();
void run();
void runAll(std::string inputDirectoryArg = "",std::string outputDirectoryArg = "",bool performIOArg = true,bool pruneImdtRelsArg = true);
void printAll([[maybe_unused]] std::string outputDirectoryArg = "");
void loadAll([[maybe_unused]] std::string inputDirectoryArg = "");
void dumpInputs();
void dumpOutputs();
SymbolTable& getSymbolTable();
RecordTable& getRecordTable();
void setNumThreads(std::size_t numThreadsValue);
void executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret);
private:
void runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg);
SymbolTableImpl symTable;
SpecializedRecordTable<0> recordTable;
Own<t_btree_ii__0_1__11__10::Type> rel_rel_46957df9a921aa76;
souffle::RelationWrapper<t_btree_ii__0_1__11__10::Type> wrapper_rel_rel_46957df9a921aa76;
Own<t_btree_ii__0_1__11::Type> rel_delta_rel_01f91f5adec19d96;
Own<t_btree_ii__0_1__11::Type> rel_new_rel_18cf54c1996edfc3;
Own<t_btree_ii__0_1__11::Type> rel_negrel_104f7d9aa50fc028;
souffle::RelationWrapper<t_btree_ii__0_1__11::Type> wrapper_rel_negrel_104f7d9aa50fc028;
Stratum_negrel_645397d4433f2251 stratum_negrel_67f37787f39d7847;
Stratum_rel_2fae15197198755a stratum_rel_7e91e7673a4c34f6;
std::string inputDirectory;
std::string outputDirectory;
SignalHandler* signalHandler{SignalHandler::instance()};
std::atomic<RamDomain> ctr{};
std::atomic<std::size_t> iter{};
};
} // namespace souffle
namespace souffle {
 Sf_hello::Sf_hello():
symTable(),
recordTable(),
rel_rel_46957df9a921aa76(mk<t_btree_ii__0_1__11__10::Type>()),
wrapper_rel_rel_46957df9a921aa76(0, *rel_rel_46957df9a921aa76, *this, "rel", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
rel_delta_rel_01f91f5adec19d96(mk<t_btree_ii__0_1__11::Type>()),
rel_new_rel_18cf54c1996edfc3(mk<t_btree_ii__0_1__11::Type>()),
rel_negrel_104f7d9aa50fc028(mk<t_btree_ii__0_1__11::Type>()),
wrapper_rel_negrel_104f7d9aa50fc028(1, *rel_negrel_104f7d9aa50fc028, *this, "negrel", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
stratum_negrel_67f37787f39d7847(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_negrel_104f7d9aa50fc028,*rel_rel_46957df9a921aa76),
stratum_rel_7e91e7673a4c34f6(symTable,recordTable,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_delta_rel_01f91f5adec19d96,*rel_new_rel_18cf54c1996edfc3,*rel_rel_46957df9a921aa76){
addRelation("rel", wrapper_rel_rel_46957df9a921aa76, false, false);
addRelation("negrel", wrapper_rel_negrel_104f7d9aa50fc028, false, true);
}

 Sf_hello::~Sf_hello(){
}

void Sf_hello::runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){

    this->inputDirectory  = std::move(inputDirectoryArg);
    this->outputDirectory = std::move(outputDirectoryArg);
    this->performIO       = performIOArg;
    this->pruneImdtRels   = pruneImdtRelsArg;

    // set default threads (in embedded mode)
    // if this is not set, and omp is used, the default omp setting of number of cores is used.
#if defined(_OPENMP)
    if (0 < getNumThreads()) { omp_set_num_threads(static_cast<int>(getNumThreads())); }
#endif

    signalHandler->set();
// -- query evaluation --
{
 std::vector<RamDomain> args, ret;
stratum_rel_7e91e7673a4c34f6.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_negrel_67f37787f39d7847.run(args, ret);
}

// -- relation hint statistics --
signalHandler->reset();
}

void Sf_hello::run(){
runFunction("", "", false, false);
}

void Sf_hello::runAll(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){
runFunction(inputDirectoryArg, outputDirectoryArg, performIOArg, pruneImdtRelsArg);
}

void Sf_hello::printAll([[maybe_unused]] std::string outputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","negrel"},{"operation","output"},{"output-dir","."},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_negrel_104f7d9aa50fc028);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf_hello::loadAll([[maybe_unused]] std::string inputDirectoryArg){
}

void Sf_hello::dumpInputs(){
}

void Sf_hello::dumpOutputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "negrel";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_negrel_104f7d9aa50fc028);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

SymbolTable& Sf_hello::getSymbolTable(){
return symTable;
}

RecordTable& Sf_hello::getRecordTable(){
return recordTable;
}

void Sf_hello::setNumThreads(std::size_t numThreadsValue){
SouffleProgram::setNumThreads(numThreadsValue);
symTable.setNumLanes(getNumThreads());
recordTable.setNumLanes(getNumThreads());
}

void Sf_hello::executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret){
if (name == "negrel") {
stratum_negrel_67f37787f39d7847.run(args, ret);
return;}
if (name == "rel") {
stratum_rel_7e91e7673a4c34f6.run(args, ret);
return;}
fatal(("unknown subroutine " + name).c_str());
}

} // namespace souffle
namespace souffle {
SouffleProgram *newInstance_hello(){return new Sf_hello;}
SymbolTable *getST_hello(SouffleProgram *p){return &reinterpret_cast<Sf_hello*>(p)->getSymbolTable();}
} // namespace souffle

#ifndef __EMBEDDED_SOUFFLE__
#include "souffle/CompiledOptions.h"
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(hello.dl)",
R"()",
R"()",
false,
R"()",
1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf_hello obj;
#if defined(_OPENMP) 
obj.setNumThreads(opt.getNumJobs());

#endif
obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir());
return 0;
} catch(std::exception &e) { souffle::SignalHandler::instance()->error(e.what());}
}
#endif

namespace souffle {
class factory_Sf_hello: souffle::ProgramFactory {
public:
SouffleProgram* newInstance();
 factory_Sf_hello();
private:
};
} // namespace souffle
namespace souffle {
SouffleProgram* factory_Sf_hello::newInstance(){
return new Sf_hello();
}

 factory_Sf_hello::factory_Sf_hello():
ProgramFactory("hello"){
}

} // namespace souffle
namespace souffle {

#ifdef __EMBEDDED_SOUFFLE__
extern "C" {
factory_Sf_hello __factory_Sf_hello_instance;
}
#endif
} // namespace souffle

