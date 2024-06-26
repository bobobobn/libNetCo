#pragma once

#include "rpc_client_stub.h"
#include "rpc_response_header.pb.h"
#include "../parameter.h"

/**
 * rpc客户端，其功能必须要在一个协程中运行
*/
namespace netco{
  class RpcClient
  {
    public:
      DISALLOW_COPY_MOVE_AND_ASSIGN(RpcClient);

      RpcClient() : m_rpc_client_stub(new RpcClientStub())
      {
        NETCO_LOG()<<("rpc_client constructor a rpc-client-stub");
      }
    
      ~RpcClient()
      {
        m_rpc_client_stub = nullptr;
        NETCO_LOG()<<("rpc_client destructor a rpc-client-stub");
      }

      void connect(const char* ip,int port)
      {
        return m_rpc_client_stub->connect(ip,port);
      }
      /**
       * @brief 进行一次rpc请求
       * @param service_name 服务名 in
       * @param method_name 方法名  in
       * @param request 请求数据    in
       * @param response 响应数据   out
       * @param header 响应头       out
      */
      void call(const std::string& service_name, const std::string& method_name, const std::string& args, std::string& response, RpcResponseHeader& header);

      /** 客户端心跳检测*/
      void ping();

      /** close the rpcclient function*/
      int close()
      {
        return m_rpc_client_stub->close();
      }
    
    private:
      std::unique_ptr<RpcClientStub> m_rpc_client_stub;
  };
}
