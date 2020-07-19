#ifndef FWK_AGGREGATE_H
#define FWK_AGGREGATE_H

// -*- C++ -*-
// author: afiq anuar
// short: aggregate of groups, with arbitrary indexing rule and attributes that are transformations of groups attributes

#include "Group.h"

namespace Framework {
  template <int N, typename ...Ts>
  class Aggregate : public Group<Ts...> {
  public:
    /// constructor
    /// don't bother, use the one below
    Aggregate() = delete;

    /// give directly the collections that one would be using
    /// not adding add_collection in order to simplify things a bit
    /// in that one can fix already the signature to cover only all the constructed collections
    template <typename ...Groups>
    Aggregate(const std::string &name_, int reserve_, Groups &...groups);

    /// provide the indexing function
    /// ie how to go from indices in each group to an index in the aggregate
    /// which common to the entire aggregate
    /// signature: args are the refs to the N groups, and returns one std::vector<std::array<int, N>> output
    template <typename Indexer>
    void set_indexer(Indexer indexer_);

    /// reserve the space for expected number of attributes
    void reserve(int attr);

    /// add an attribute into the collection
    /// returns false upon failure to add the attribute
    /// this can happen if some data types are inconsistent
    /// returns true upon a successful addition
    /// the attributes refer to the attributes of the underlying groups
    /// syntax needs to be as expected by inquire_collection
    template <typename Function, typename ...Attributes>
    bool add_attribute(const std::string &attr, Function function, Attributes &&...attrs);

    /// transform a group of internal attributes into another attribute
    /// the transformation is done element-wise on every element of held data
    /// as this adds a new attribute, its name has to be unique
    template <typename Function, typename ...Attributes>
    bool transform_attribute(const std::string &attr, Function function, Attributes &&...attrs);

    /// populate the data by calling the functions provided
    void populate(long long) override;

  protected:
    /// inquire attribute of the underlying groups
    /// similar to the above, but now an array: 
    /// first collection index in v_group, second the attribute index within it
    /// assumes syntax of group::attribute
    std::array<int, 2> inquire_group(const std::string &name);

    /// ie the actual reference to the element returned by inquire_group
    /// necessarily implemented without safety...
    const std::variant<std::vector<Ts>...>& underlying_attribute(const std::string &name);

    /// indexing function - how to go from indices in each group to an index in the aggregate
    std::function<void()> indexer;

    /// and the indices that are made by the above
    std::vector<std::array<int, N>> v_indices;

    /// just a flag for each attribute whether it is external or internal
    /// external 1 are attributes that are transformed from groups' underlying attributes
    /// internal 0 are attributes transformed from this aggregate's external attributes
    std::vector<int> v_flag;

    /// references to the groups
    std::array<std::reference_wrapper<Group<Ts...>>, N> v_group;
  };

  /// deduction guides for convenience
  template <typename ...Ts, typename ...Groups> 
  Aggregate(const char *, int, Group<Ts...> &, Groups &...) -> Aggregate<sizeof...(Groups) + 1, Ts...>;

  template <typename ...Ts, typename ...Groups> 
  Aggregate(const std::string &, int, Group<Ts...> &, Groups &...) -> Aggregate<sizeof...(Groups) + 1, Ts...>;
}

#include "Aggregate.cc"

#endif
