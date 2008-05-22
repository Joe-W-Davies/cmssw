#ifndef CondCore_IOVService_IOVProxy_h
#define CondCore_IOVService_IOVProxy_h

#include <string>
#include "CondCore/DBCommon/interface/Time.h"
#include <boost/shared_ptr.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>

namespace cond {
  
  class IOV;
  class PoolTransaction;
  
  class IOVElement {
  public:
    IOVElement() : m_since(0), m_till(0), db(0){}
    IOVElement(PoolTransaction * idb) : m_since(0), m_till(0), db(idb){}
    IOVElement(cond::Time_t is,
	       cond::Time_t it,
	       std::string const& itoken,
	       PoolTransaction * idb) :
      m_since(is), m_till(it), m_token(itoken), db(idb){}
    
    void set(cond::Time_t is,
	     cond::Time_t it,
	     std::string const& itoken ) {
      m_since=is; m_till=it; m_token=itoken;
    }
    
    void set(IOV const & v, int i);
    
    cond::Time_t since() const {return m_since;}
    cond::Time_t till() const {return m_till;}
    std::string const & payloadToken() const {return m_token;}

  private:
    cond::Time_t m_since;
    cond::Time_t m_till;
    std::string  m_token;
    PoolTransaction * db;
  };
  
  
  namespace impl {
    struct IOVImpl;
  }
  
  /* IOV as the user wants it
   */
  class IOVProxy {
  public:
    
    IOVProxy();
    ~IOVProxy();
    
    IOVProxy(cond::PoolTransaction& db,
	     const std::string & token);
    
    struct IterHelp {
      typedef IOVElement result_type;
      IterHelp(impl::IOVImpl & in);
      
      result_type const & operator()(int i) const {
	elem.set(iov,i);
	return elem;
      } 
      
    private:
      IOV const & iov;
      mutable IOVElement elem;
    };
    
    typedef boost::transform_iterator<IterHelp,boost::counting_iterator<int> > const_iterator;
    
    const_iterator begin() const {
      return  boost::make_transform_iterator(boost::counting_iterator<int>(0),
					     IterHelp(*m_iov));
    }
    
    const_iterator end() const {
      return  boost::make_transform_iterator(boost::counting_iterator<int>(size()),
					     IterHelp(*m_iov));
    }
    
    
    int size() const;
    IOV const & iov() const;
    TimeType timetype() const;
    
  private:
    boost::shared_ptr<impl::IOVImpl> m_iov;
    
  };
}

#endif // CondCore_IOVService_IOVProxy_h
