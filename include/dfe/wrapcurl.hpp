#ifndef DFE_WRAPCURL_HPP
#define DFE_WRAPCURL_HPP

#include<curl/curl.h>
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<vector>
#include<unordered_map>
#include<cstring>
#include<stdexcept>
#include<type_traits>
#include<memory>

/**
*  @namespace dfe
*  @brief deep-fried-eggplant.com
*/
namespace dfe{

    /**
     * @class WrapCurl
     * @brief cURL handler class, and actually it only contains values of cURL option.
    */
    class WrapCurl;

    /**
     * @namespace detail
     * @brief detail implement
    */
    namespace detail{
        enum class WrapCurlOptionBool   : uint16_t;
        enum class WrapCurlOptionLong   : uint16_t;
        enum class WrapCurlOptionString : uint16_t;
    }

    namespace exception{
        class WrapCurlException;
    }
}

namespace std{
    template<>
    struct hash<dfe::detail::WrapCurlOptionBool>{
        size_t operator()(dfe::detail::WrapCurlOptionBool x) const noexcept{
            return static_cast<std::underlying_type<dfe::detail::WrapCurlOptionBool>::type>(x);
        }
    };
    template<>
    struct hash<dfe::detail::WrapCurlOptionLong>{
        size_t operator()(dfe::detail::WrapCurlOptionLong x) const noexcept{
            return static_cast<std::underlying_type<dfe::detail::WrapCurlOptionLong>::type>(x);
        }
    };
    template<>
    struct hash<dfe::detail::WrapCurlOptionString>{
        size_t operator()(dfe::detail::WrapCurlOptionString x) const noexcept{
            
            return static_cast<std::underlying_type<dfe::detail::WrapCurlOptionString>::type>(x);
        }
    };
}

namespace dfe{

    class WrapCurl{
        public:
        using Header=std::unordered_map<std::string,std::string>;
        using Params=std::unordered_map<std::string,std::string>;
        using Bool  =bool;
        using Long  =long;
        using String=std::string;
        using Istream=std::istream;

        /**
         * @struct Response
         * @brief the response of the HTTP request done
        */
        struct Response;

        /**
         * @class FormData
         * @brief a container class of the multipart/form-data contents
        */
        struct FormData;

        class Option;

        enum class HttpVersion  : Long;

        private:
        CURL* _curl;
        std::unordered_map<detail::WrapCurlOptionBool  ,Bool  > _optionBoolList  ;
        std::unordered_map<detail::WrapCurlOptionLong  ,Long  > _optionLongList  ;
        std::unordered_map<detail::WrapCurlOptionString,String> _optionStringList;
        
        public:
        WrapCurl();
        ~WrapCurl();

        /**
         * @fn Response get(const std::string& url)
         * @brief perform a GET request
         * @param url URL where you want to perform the request
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response get(const String& url);

        /**
         * @fn Response get(const std::string& url,const Header& header)
         * @brief perform a GET request
         * @param url URL where you want to perform the request
         * @param header HTTP header in the form of std::unordered_map<std::string,std::string>
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response get(const String& url,const Header& header);
        
        /**
         * @fn Response post(const std::string& url,const std::string& postData)
         * @brief perform a POST request
         * @param url URL where you want to perform the request
         * @param postData the data to post
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response post(const String& url,const String& postData);
        
        /**
         * @fn Response post(const std::string& url,const std::string& postData,const Header& header)
         * @brief perform a POST request
         * @param url URL where you want to perform the request
         * @param postData the data to post
         * @param header HTTP header in the form of std::unordered_map<std::string,std::string>
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response post(const String& url,const String& postData,const Header& header);
        
        /**
         * @fn Response post(const std::string& url,FILE* fp)
         * @brief perform a POST request
         * @param url URL where you want to perform the request
         * @param fp a file pointer that points to the file which its contents is the data you want to post 
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response post(const String& url,FILE* fp);

        Response post(const String& url,Istream& istream);
        
        /**
         * @fn Response post(const std::string& url,FILE* fp,const Header& header)
         * @brief perform a POST request
         * @param url URL where you want to perform the request
         * @param fp a file pointer that points to the file which its contents is the data you want to post
         * @param header HTTP header in the form of std::unordered_map<std::string,std::string>
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response post(const String& url,FILE* fp,const Header& header);

        Response post(const String& url,Istream& istream,const Header& header);

        /**
         * @fn Response post(const std::string& url,const FormData& formData)
         * @brief perform a POST request
         * @param url URL where you want to perform the request
         * @param formData the data to post in the form of FormData class that have multipart/form-data contents.
         * @param header HTTP header in the form of std::unordered_map<std::string,std::string>
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response post(const String& url,const FormData& formData);

        /**
         * @fn Response post(const std::string& url,const FormData& formData,const Header& header)
         * @brief perform a POST request
         * @param url URL where you want to perform the request
         * @param formData the data to post in the form of FormData class that have multipart/form-data contents.
         * @param header HTTP header in the form of std::unordered_map<std::string,std::string>
         * @throw exception::WrapCurlException if some trouble has occured with the cURL handler
         * @return HTTP response if succeed
        */
        Response post(const String& url,const FormData& formData,const Header& header);

        /**
         * @fn void setOption(const detail::WrapCurlOptionBool option,const bool value)
         * @brief set cURL option
         * @param option enum class WrapCurlOptionBool (defined as WrapCurl::detail::WrapCurlOptionBool) that specifies boolean-type cURL option
         * @param value true/false 
        */
        void setOption(const detail::WrapCurlOptionBool   option, const Bool value);

        /**
         * @fn void setOption(const detail::WrapCurlOptionLong option,const long value)
         * @brief set cURL option
         * @param option enum class WrapCurlOptionLong (defined as WrapCurl::detail::WrapCurlOptionLong) that specifies long-integer-type cURL option
         * @param value the number as the cURL option's value
        */
        void setOption(const detail::WrapCurlOptionLong   option, const Long value);

        template<typename NumberT>
        void setOption(const detail::WrapCurlOptionLong   option, const NumberT value);
        
        /**
         * @fn void eraseOption(const detail::WrapCurlOptionString option,const std::string value)
         * @brief set cURL option
         * @param option enum class WrapCurlOptionString (defined as WrapCurl::detail::WrapCurlOptionString) that specifies string-type cURL option
         * @param value true/false 
        */
        void setOption(const detail::WrapCurlOptionString option, const String value);


        template<typename T>
        void setOption(const detail::WrapCurlOptionBool,const T)=delete;
        template<typename T>
        void setOption(const detail::WrapCurlOptionLong,const T*)=delete;
        void setOption(const detail::WrapCurlOptionLong,const bool)=delete;


        void eraseOption(const detail::WrapCurlOptionBool   option);
        void eraseOption(const detail::WrapCurlOptionLong   option);
        void eraseOption(const detail::WrapCurlOptionString option);
        void clearOptions();

        private:
        void applyOption(CURL* curl);
        void applyHeader(curl_slist* slist,const Header& header);

        static size_t writeCallback (char* ptr,size_t size,size_t nmemb,void* body   );
        static size_t headerCallback(char* ptr,size_t size,size_t nmemb,void* header );
        static size_t readCallback  (char* ptr,size_t size,size_t nmemb,void* istream);
        static void setWriteData (CURL* curl,String* body  );
        static void setHeaderData(CURL* curl,String* header);
        static void setReadData  (CURL* curl,std::istream& is);

        public:
    
        /**
         * @fn urlEncode
         * @brief create a url-encoded string
         * @param str the string to be encoded
         * @return a url-encoded string
        */
        static std::string urlEncode(const std::string& str);
        
        /**
         * @fn urlEncode
         * @brief create a url-encoded string
         * @param data the data to be encoded in the form of std::unordered_map<std::string,std::string>
         * @return a url-encoded string
        */
        static std::string urlEncode(const Params& data);
    };

    enum class detail::WrapCurlOptionBool   : uint16_t{
        Verbose         = CURLOPT_VERBOSE        ,
        NoSignal        = CURLOPT_NOSIGNAL       ,
        AutoReferer     = CURLOPT_AUTOREFERER    ,
        FollowLocation  = CURLOPT_FOLLOWLOCATION ,
        SslVerifyPeer   = CURLOPT_SSL_VERIFYPEER ,
    };
    enum class detail::WrapCurlOptionLong   : uint16_t{
        Timeout         = CURLOPT_TIMEOUT        ,
        Port            = CURLOPT_PORT           ,
        HttpVersion     = CURLOPT_HTTP_VERSION   ,
        FileSize        = CURLOPT_INFILESIZE
    };
    enum class detail::WrapCurlOptionString : uint16_t{
        UserAgent       = CURLOPT_USERAGENT      ,
        CaInfo          = CURLOPT_CAINFO         ,
        Proxy           = CURLOPT_PROXY          ,
        ProxyCaInfo     = CURLOPT_PROXY_CAINFO   ,
        CookieFile      = CURLOPT_COOKIEFILE     ,
        CookieJar       = CURLOPT_COOKIEJAR
    };
    
    class exception::WrapCurlException : public std::runtime_error{
        CURLcode _curlCode;
        public:
        WrapCurlException(const CURLcode curlCode):runtime_error(curl_easy_strerror(curlCode)),_curlCode(curlCode){}
        CURLcode curlCode(){return _curlCode;}
    };

    struct WrapCurl::Response{
        long status;
        std::string header;
        std::string body;
    };

    struct WrapCurl::FormData{
        friend class ::dfe::WrapCurl;
        private:
        struct Data{
            char* name;
            bool isFilePath;
            char* data;
            std::size_t dataSize;
            char* fileName;
            curl_slist* header;

            Data();
            ~Data();
        };
        struct DataNode{
            Data data;
            DataNode* next;
            void clear();
        };
        DataNode* _node;

        Data& makeNewNode();
        
        public:
        FormData();
        ~FormData();

        FormData(const FormData& other)=delete;
        FormData& operator=(const FormData& other)=delete;

        void addData(const std::string& name,const std::string& data);
        void addData(const std::string& name,const std::string& data,const WrapCurl::Header& header);
        void addData(const std::string& name,const std::string& data,const std::string& fileName);
        void addData(const std::string& name,const std::string& data,const std::string& fileName,const WrapCurl::Header& header);
        void addFile(const std::string& name,const std::string& filePath);
        void addFile(const std::string& name,const std::string& filePath,const WrapCurl::Header& header);
        void addFile(const std::string& name,const std::string& filePath,const std::string& fileName);
        void addFile(const std::string& name,const std::string& filePath,const std::string& fileName,const WrapCurl::Header& header);

        private:
        void apply(curl_mime* mime) const;
        static char* copyString(const String& str);
        static char* copyData(const String& data,size_t& size);
    };

    enum class WrapCurl::HttpVersion : WrapCurl::Long{
        Any         = CURL_HTTP_VERSION_NONE ,
        Http1       = CURL_HTTP_VERSION_1_0  ,
        Http1_1     = CURL_HTTP_VERSION_1_1  ,
        Http2       = CURL_HTTP_VERSION_2_0  ,
        Http2TLS    = CURL_HTTP_VERSION_2TLS
    };


    class WrapCurl::Option{
        Option()=delete;
        public:
        using BoolType   = detail::WrapCurlOptionBool   ;
        using LongType   = detail::WrapCurlOptionLong   ;
        using StringType = detail::WrapCurlOptionString ;
        
        #if __cplusplus < 202002L
        static constexpr LongType   Timeout         = LongType::Timeout         ;
        static constexpr LongType   Port            = LongType::Port            ;
        static constexpr LongType   HttpVersion     = LongType::HttpVersion     ;
        static constexpr BoolType   Verbose         = BoolType::Verbose         ;
        static constexpr BoolType   AutoReferer     = BoolType::AutoReferer     ;
        static constexpr BoolType   FollowLocation  = BoolType::FollowLocation  ;
        static constexpr BoolType   SslVerifyPeer   = BoolType::SslVerifyPeer   ;
        static constexpr StringType UserAgent       = StringType::UserAgent     ;
        static constexpr StringType CaInfo          = StringType::CaInfo        ;
        static constexpr StringType Proxy           = StringType::Proxy         ;
        static constexpr StringType ProxyCaInfo     = StringType::ProxyCaInfo   ;
        static constexpr StringType CookieFile      = StringType::CookieFile    ;
        static constexpr StringType CookieJar       = StringType::CookieJar     ;
        #else
        using enum BoolType;
        using enum LongType;
        using enum StringType;
        #endif
    };


    WrapCurl::WrapCurl():_optionBoolList({}),_optionLongList({}),_optionStringList({}){}
    WrapCurl::~WrapCurl(){}

    WrapCurl::Response WrapCurl::get(const String& url){
        return get(url,{});
    }
    WrapCurl::Response WrapCurl::get(const String& url, const Header& header){
        CURL* curl;
        CURLcode curlCode;
        curl_slist* curlHeader=nullptr;

        Response response;

        curl=curl_easy_init();
        
        if(curl != nullptr){
            for(auto item : header){
                curlHeader=curl_slist_append(curlHeader,std::string(item.first+":"+item.second).c_str());
            }

            setHeaderData(curl,&(response.header));
            setWriteData(curl,&(response.body));

            curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
            curl_easy_setopt(curl,CURLOPT_HTTPHEADER,curlHeader);
            applyOption(curl);
            
            curlCode = curl_easy_perform(curl);

            if(curlCode==CURLE_OK){
                curl_easy_getinfo(curl,CURLINFO_HTTP_CODE,&(response.status));
            }

            curl_easy_cleanup(curl);
            curl_slist_free_all(curlHeader);

            if(curlCode!=CURLE_OK){
                throw exception::WrapCurlException(curlCode);
            }
        }else{
            throw exception::WrapCurlException(CURLE_FAILED_INIT);
        }

        return response;
    }

    WrapCurl::Response WrapCurl::post(const String& url,const String& postData){
        return post(url,postData,{});
    }
    WrapCurl::Response WrapCurl::post(const String& url,const String& postData,const Header& header){
        CURL* curl;
        CURLcode curlCode;
        curl_slist* curlHeader=NULL;

        Response response;

        curl=curl_easy_init();
        
        if(curl != nullptr){
            for(auto item : header){
                curlHeader=curl_slist_append(curlHeader,std::string(item.first+":"+item.second).c_str());
            }

            setHeaderData(curl,&(response.header));
            setWriteData(curl,&(response.body));

            curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER,curlHeader);
            curl_easy_setopt(curl, CURLOPT_POST,1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postData.length());
            applyOption(curl);

            curlCode = curl_easy_perform(curl);
            
            if(curlCode==CURLE_OK){
                curl_easy_getinfo(curl,CURLINFO_HTTP_CODE,&(response.status));
            }
            
            curl_easy_cleanup(curl);
            curl_slist_free_all(curlHeader);
            
            if(curlCode!=CURLE_OK){
                throw exception::WrapCurlException(curlCode);
            }
        }else{
            throw exception::WrapCurlException(CURLE_FAILED_INIT);
        }
        return response;
    }
    WrapCurl::Response WrapCurl::post(const String& url,Istream& istream){
        return post(url,istream,{});
    }
    WrapCurl::Response WrapCurl::post(const String& url,Istream& istream,const Header& header){
        CURL* curl;
        CURLcode curlCode;
        curl_slist* curlHeader=nullptr;

        Response response;

        curl=curl_easy_init();
        
        if(curl != nullptr){
            for(auto item : header){
                curlHeader=curl_slist_append(curlHeader,std::string(item.first+":"+item.second).c_str());
            }

            setHeaderData(curl,&(response.header));
            setWriteData(curl,&(response.body));
            setReadData(curl,istream);

            curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
            curl_easy_setopt(curl,CURLOPT_HTTPHEADER,curlHeader);
            curl_easy_setopt(curl,CURLOPT_POST,1);

            applyOption(curl);

            curlCode = curl_easy_perform(curl);

            if(curlCode==CURLE_OK){
                curl_easy_getinfo(curl,CURLINFO_HTTP_CODE,&(response.status));
            }
            curl_easy_cleanup(curl);
            curl_slist_free_all(curlHeader);
            if(curlCode!=CURLE_OK){
                throw exception::WrapCurlException(curlCode);
            }
        }else{
            throw exception::WrapCurlException(CURLE_FAILED_INIT);
        }
        return response;
    }
    WrapCurl::Response WrapCurl::post(const String& url,const FormData& formData){
        return post(url,formData,{});
    }
    WrapCurl::Response WrapCurl::post(const String& url,const FormData& formData,const Header& header){
        CURL* curl;
        CURLcode curlCode;
        curl_slist* curlHeader=nullptr;
        curl_mime* mime;

        Response response;

        curl=curl_easy_init();
        
        if(curl != nullptr){
            for(auto item : header){
                curlHeader=curl_slist_append(curlHeader,std::string(item.first+":"+item.second).c_str());
            }
            mime=curl_mime_init(curl);
            formData.apply(mime);

            setHeaderData(curl,&(response.header));
            setWriteData(curl,&(response.body));

            curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
            curl_easy_setopt(curl,CURLOPT_HTTPHEADER,curlHeader);
            curl_easy_setopt(curl,CURLOPT_MIMEPOST,mime);

            applyOption(curl);

            curlCode = curl_easy_perform(curl);

            if(curlCode==CURLE_OK){
                curl_easy_getinfo(curl,CURLINFO_HTTP_CODE,&(response.status));
            }
            curl_easy_cleanup(curl);
            curl_slist_free_all(curlHeader);
            curl_mime_free(mime);
            if(curlCode!=CURLE_OK){
                throw exception::WrapCurlException(curlCode);
            }
        }else{
            throw exception::WrapCurlException(CURLE_FAILED_INIT);
        }
        return response;
    }
    

    void WrapCurl::setOption(const detail::WrapCurlOptionBool option,const Bool value){
        _optionBoolList[option]=value;
    }
    void WrapCurl::setOption(const detail::WrapCurlOptionLong option,const Long value){
        _optionLongList[option]=value;
    }
    template<typename NumberT>
    void WrapCurl::setOption(const detail::WrapCurlOptionLong option,const NumberT value){
        static_assert(
            std::is_enum<NumberT>::value
                || std::is_integral<NumberT>::value
                || std::is_floating_point<NumberT>::value,
            "NumberT must be integral, floating-point, or enum, but is not"
        );
        this->setOption(option,static_cast<Long>(value));
    }
    void WrapCurl::setOption(const detail::WrapCurlOptionString option,const String value){
        _optionStringList[option]=value;
    }
    void WrapCurl::eraseOption(const detail::WrapCurlOptionBool option){
        _optionBoolList.erase(option);
    }
    void WrapCurl::eraseOption(const detail::WrapCurlOptionLong option){
        _optionLongList.erase(option);
    }
    void WrapCurl::eraseOption(const detail::WrapCurlOptionString option){
        _optionStringList.erase(option);
    }
    void WrapCurl::clearOptions(){
        _optionBoolList.clear();
        _optionLongList.clear();
        _optionStringList.clear();
    }

    void WrapCurl::applyOption(CURL* curl){
        for(auto item : _optionBoolList){
            curl_easy_setopt(curl,(CURLoption)(long)item.first,item.second);
        }
        for(auto item : _optionLongList){
            curl_easy_setopt(curl,(CURLoption)(long)item.first,item.second);
        }
        for(auto item : _optionStringList){
            curl_easy_setopt(curl,(CURLoption)(long)item.first,item.second.c_str());
        }
    }
    void WrapCurl::setWriteData(CURL* curl,std::string* body){
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writeCallback);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)body);
    }
    void WrapCurl::setHeaderData(CURL* curl,std::string* header){
        curl_easy_setopt(curl,CURLOPT_HEADERFUNCTION,headerCallback);
        curl_easy_setopt(curl,CURLOPT_HEADERDATA,(void*)header);
    }
    void WrapCurl::setReadData(CURL* curl,Istream& istream){
        curl_easy_setopt(curl,CURLOPT_READFUNCTION,readCallback);
        curl_easy_setopt(curl,CURLOPT_READDATA,(void*)&istream);
    }
    size_t WrapCurl::writeCallback(char* ptr,size_t size,size_t nmemb,void* body){
        std::string* p=static_cast<std::string*>(body);
        size_t s=size*nmemb;
        p->append(ptr,s);
        return s;
    }
    size_t WrapCurl::headerCallback(char* ptr,size_t size,size_t nmemb,void* header){
        std::string* p=static_cast<std::string*>(header);
        size_t s=size*nmemb;
        p->append(ptr,s);
        return s;
    }
    size_t WrapCurl::readCallback(char* ptr,size_t size,size_t nmemb,void* istream){
        Istream* p=static_cast<Istream*>(istream);
        size_t s=size*nmemb;
        p->read(ptr,s);
        return p->gcount();
    }

    std::string WrapCurl::urlEncode(const std::string& str){
        std::ostringstream oss;
        for(char ch : str){
            if(
                (ch>='A' && ch<='Z')||
                (ch>='a' && ch<='z')||
                (ch>='0' && ch<='9')||
                ch=='-'  || ch=='~' ||
                ch=='_'  || ch=='.'
            ){
                oss << ch;
            }else{
                char buf[3];
                sprintf(buf,"%02X",uint8_t(ch));
                oss << '%' << std::string(buf);
            }
        }
        return oss.str();
    }
    std::string WrapCurl::urlEncode(const Params& data){
        std::ostringstream oss;
        for(auto it=data.begin(); it!=data.end(); it++){
            auto item=*it;
            if(it!=data.begin()){
                oss << "&";
            }
            oss << urlEncode(it->first)
                << '='
                << urlEncode(it->second);
        }
        return oss.str();
    }

    WrapCurl::FormData::Data::Data()
    :   name(nullptr),isFilePath(false),data(nullptr),
        dataSize(0),fileName(nullptr),header(nullptr)
    {}
    WrapCurl::FormData::Data::Data::~Data(){
        delete data;
        delete fileName;
        curl_slist_free_all(header);
    }
    void WrapCurl::FormData::DataNode::clear(){
        if(next){
            next->clear();
            delete next;
        }
    }

    WrapCurl::FormData::FormData()
    :   _node(nullptr)
    {}
    WrapCurl::FormData::~FormData(){
        if(_node){
            _node->clear();
            delete _node;
        }
    }

    WrapCurl::FormData::Data& WrapCurl::FormData::makeNewNode(){
        DataNode* node=new DataNode();
        node->next=this->_node;
        this->_node=node;
        return _node->data;
    }
    void WrapCurl::FormData::addData(const String& name,const String& data){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyData(data,d.dataSize);
        d.isFilePath=false;
    }
    void WrapCurl::FormData::addData(const String& name,const String& data,const Header& header){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyData(data,d.dataSize);
        d.isFilePath=true;
        for(auto it=header.begin(); it!=header.end(); ++it){
            d.header=curl_slist_append(d.header,(it->first+':'+it->second).c_str());
        }
    }
    void WrapCurl::FormData::addData(const String& name,const String& data,const String& fileName){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyData(data,d.dataSize);
        d.fileName=copyString(fileName);
        d.isFilePath=false;
    }
    void WrapCurl::FormData::addData(const String& name,const String& data,const String& fileName,const Header& header){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyData(data,d.dataSize);
        d.fileName=copyString(fileName);
        d.isFilePath=false;
        for(auto it=header.begin(); it!=header.end(); ++it){
            d.header=curl_slist_append(d.header,(it->first+':'+it->second).c_str());
        }
    }
    void WrapCurl::FormData::addFile(const String& name,const String& filePath){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyString(filePath);
        d.isFilePath=true;
    }
    void WrapCurl::FormData::addFile(const String& name,const String& filePath,const Header& header){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyString(filePath);
        d.isFilePath=true;
        for(auto it=header.begin(); it!=header.end(); ++it){
            d.header=curl_slist_append(d.header,(it->first+':'+it->second).c_str());
        }
    }
    void WrapCurl::FormData::addFile(const String& name,const String& filePath,const String& fileName){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyString(filePath);
        d.fileName=copyString(fileName);
        d.isFilePath=true;
    }
    void WrapCurl::FormData::addFile(const String& name,const String& filePath,const String& fileName,const Header& header){
        Data& d=makeNewNode();
        d.name=copyString(name);
        d.data=copyString(filePath);
        d.fileName=copyString(fileName);
        d.isFilePath=true;
        for(auto it=header.begin(); it!=header.end(); ++it){
            d.header=curl_slist_append(d.header,(it->first+':'+it->second).c_str());
        }
    }

    void WrapCurl::FormData::apply(curl_mime* mime) const{
        curl_mimepart* part;
        for(DataNode* node=_node; bool(node); node=node->next){
            Data& item=node->data;
            part=curl_mime_addpart(mime);
            curl_mime_name(part,item.name);
            if(item.data!=nullptr){
                if(item.isFilePath){
                    curl_mime_filedata(part,item.data);
                }else{
                    curl_mime_data(part,item.data,item.dataSize);
                }
            }
            if(item.fileName!=nullptr){
                curl_mime_filename(part,item.fileName);
            }
            if(item.header!=nullptr){
                curl_mime_headers(part,item.header,0);
            }
        }
    }

    char* WrapCurl::FormData::copyString(const String& str){
        std::size_t size=str.size();
        char* ptr=new char[size+1];
        mempcpy(ptr,str.c_str(),size);
        ptr[size]=0;
        return ptr;
    }

    char* WrapCurl::FormData::copyData(const String& str,size_t& size){
        size=str.size();
        char* ptr=new char[size+1];
        memcpy(ptr,str.c_str(),size);
        ptr[size]=0;
        return ptr;
    }
}

#endif