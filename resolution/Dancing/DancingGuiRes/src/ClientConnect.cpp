//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : ConnectManager.cpp
//  @ Date : 2012/12/7
//  @ Author :
//
//


#include "ClientConnect.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "DancingGuiSys.h"
#define TEST
ConnectManager::ConnectManager(void)
{
    //��������󴴽�
    m_clientPtr = RakNet::RakPeerInterface::GetInstance();

    m_clientID = RakNet::UNASSIGNED_SYSTEM_ADDRESS;

    strcpy(m_clientPort, "0");
    strcpy(m_ip, "127.0.0.1");
    strcpy(m_serverPort, "1234");
}
ConnectManager::~ConnectManager(void)
{
    m_clientPtr->Shutdown(300);

    // We're done with the network
    RakNet::RakPeerInterface::DestroyInstance(m_clientPtr);
}
void ConnectManager::ConfigClient(void)
{

}
void ConnectManager::StartUpClient(void)
{
    RakNet::SocketDescriptor socketDescriptor(atoi(m_clientPort), 0);
    socketDescriptor.socketFamily = AF_INET;
    m_clientPtr->Startup(8, &socketDescriptor, 1);
    m_clientPtr->SetOccasionalPing(true);

    RakNet::ConnectionAttemptResult car = m_clientPtr->Connect(m_ip, atoi(m_serverPort), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"));
    RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);


}
void ConnectManager::Send(string tempstring, string tempstring2) //use for send message   ,it will appear in a main loop
{

    //cin >> m_message;
    if (strcmp(tempstring.c_str(), "newhouse") == 0)
    {
        string tempHouseName;
        {
            //���ͷ�����Ϣ
            mTypeId = CS_CREATE_HOUSE;
            RakNet::BitStream mBitStream ;
            mBitStream.Write(mTypeId);

            string tempHouseDancestyle;
            string tempHouseDancemusic;
            string tempHouseDancescene;


            TiXmlDocument myDocument ;//= new TiXmlDocument();
            myDocument.LoadFile("newhouse.xml");
            //��ø�Ԫ�أ���Persons��
            TiXmlElement *RootElement = myDocument.RootElement();//roles

            TiXmlElement *Person = RootElement->FirstChildElement();
            tempHouseName = Person->Attribute("name");
            tempHouseDancestyle = Person->Attribute("dancestyle");
            tempHouseDancemusic = Person->Attribute("dancemusic");
            tempHouseDancescene = Person->Attribute("dancescene");

            mBitStream.Write(tempHouseName);
            mBitStream.Write(tempHouseDancestyle);
            mBitStream.Write(tempHouseDancemusic);
            mBitStream.Write(tempHouseDancescene);

            m_clientPtr->Send(&mBitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
        }
        {
            mTypeId = CS_LOGIN_HOUSE;
            RakNet::BitStream mBitStream ;
            mBitStream.Write(mTypeId);

            string tempRoleName;
            bool   tempRoleSex;
            string tempRoleHire;
            string tempRoleDecorate;
            string tempRoleUpware;
            string tempRoleDownware;
            string tempRoleShoe;

            {
                TiXmlDocument myDocument ;//= new TiXmlDocument();
                myDocument.LoadFile("myhouse.xml");
                //��ø�Ԫ�أ���Persons��
                TiXmlElement *RootElement = myDocument.RootElement();//roles

                TiXmlElement *Person = RootElement->FirstChildElement();

                tempHouseName = Person->Attribute("name");
            }
            {

                TiXmlDocument myDocument ;//= new TiXmlDocument();
                myDocument.LoadFile("myrole.xml");
                //��ø�Ԫ�أ���Persons��
                TiXmlElement *RootElement = myDocument.RootElement();//roles

                TiXmlElement *Person = RootElement->FirstChildElement();

                tempRoleName = Person->Attribute("name");
                tempRoleSex = Person->Attribute("sex");
                tempRoleHire = Person->Attribute("hire");
                tempRoleDecorate = Person->Attribute("decorate");
                tempRoleUpware = Person->Attribute("upware");
                tempRoleDownware = Person->Attribute("downware");
                tempRoleShoe = Person->Attribute("shoe");
            }



            mBitStream.Write(tempHouseName);
            mBitStream.Write(tempRoleName);
            mBitStream.Write(tempRoleSex);
            mBitStream.Write(tempRoleHire);
            mBitStream.Write(tempRoleDecorate);
            mBitStream.Write(tempRoleShoe);
            mBitStream.Write(tempRoleUpware);
            //mBitStream.Write(tempRoleDownware);

            m_clientPtr->Send(&mBitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
        }
    }
    if (strcmp(tempstring.c_str(), "houselist") == 0)
    {
        mTypeId = CS_GET_HOUSES_LIST;
        RakNet::BitStream mBitStream ;
        mBitStream.Write(mTypeId);
        m_clientPtr->Send(&mBitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

    }
    if (strcmp(tempstring.c_str(), "login") == 0)
    {
        //tempstring2
        mTypeId = CS_LOGIN_HOUSE;
        RakNet::BitStream mBitStream ;
        mBitStream.Write(mTypeId);


        string tempHouseName = tempstring2;


        string tempRoleName;
        bool   tempRoleSex;
        string tempRoleHire;
        string tempRoleDecorate;
        string tempRoleUpware;
        string tempRoleDownware;
        string tempRoleShoe;


        //��ȡ��������Ϣ
        TiXmlDocument myDocument ;//= new TiXmlDocument();
        myDocument.LoadFile("myrole.xml");
        //��ø�Ԫ�أ���Persons��
        TiXmlElement *RootElement = myDocument.RootElement();//roles

        TiXmlElement *Person = RootElement->FirstChildElement();

        tempRoleName = Person->Attribute("name");
        tempRoleSex = Person->Attribute("sex");
        tempRoleHire = Person->Attribute("hire");
        tempRoleDecorate = Person->Attribute("decorate");
        tempRoleUpware = Person->Attribute("upware");
        tempRoleDownware = Person->Attribute("downware");
        tempRoleShoe = Person->Attribute("shoe");

        mBitStream.Write(tempHouseName);

        mBitStream.Write(tempRoleName);
        mBitStream.Write(tempRoleSex);
        mBitStream.Write(tempRoleHire);
        mBitStream.Write(tempRoleDecorate);
        mBitStream.Write(tempRoleUpware);
        mBitStream.Write(tempRoleDownware);
        //mBitStream.Write(tempRoleShoe);//fux add ������Ϣ��δ����

        m_clientPtr->Send(&mBitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
    }
    if (strcmp(tempstring.c_str(), "logoff") == 0)
    {
        mTypeId = CS_LOGOFF_HOUSE;
        RakNet::BitStream mBitStream ;
        mBitStream.Write(mTypeId);

        string tempHouseName;
        string tempRoleName;

        {
            TiXmlDocument myDocument ;//= new TiXmlDocument();
            myDocument.LoadFile("myrole.xml");
            //��ø�Ԫ�أ���Persons��
            TiXmlElement *RootElement = myDocument.RootElement();//roles

            TiXmlElement *Person = RootElement->FirstChildElement();

            tempRoleName = Person->Attribute("name");
        }
        {

            TiXmlDocument myDocument ;//= new TiXmlDocument();
            myDocument.LoadFile("myhouse.xml");
            //��ø�Ԫ�أ���Persons��
            TiXmlElement *RootElement = myDocument.RootElement();//roles

            TiXmlElement *Person = RootElement->FirstChildElement();

            tempHouseName = Person->Attribute("name");
        }
        {
            TiXmlDocument myDocument ;
            myDocument.SaveFile("myhouse.xml");
        }

        mBitStream.Write(tempHouseName);
        mBitStream.Write(tempRoleName);

        m_clientPtr->Send(&mBitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
    }

}
void ConnectManager::Receive(void)//use for receive message   ,it will appear in a main loop
{
    for (m_packetPtr = m_clientPtr->Receive(); m_packetPtr; m_clientPtr->DeallocatePacket(m_packetPtr), m_packetPtr = m_clientPtr->Receive())
    {
        RakNet::BitStream tempBitstream(m_packetPtr->data, m_packetPtr->length, false);
        RakNet::RakNetGUID tempGuid = m_packetPtr->guid;

        tempBitstream.Read(m_packetIdentifier);


        // Check if this is a network message packet
        switch (m_packetIdentifier)
        {
        case ID_DISCONNECTION_NOTIFICATION:
            // Connection lost normally
            printf("ID_DISCONNECTION_NOTIFICATION\n");
            break;
        case ID_ALREADY_CONNECTED:
            // Connection lost normally
            printf("ID_ALREADY_CONNECTED with guid %"PRINTF_64_BIT_MODIFIER"u\n", m_packetPtr->guid);
            break;
        case ID_INCOMPATIBLE_PROTOCOL_VERSION:
            printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
            break;
        case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
            printf("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
            break;
        case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
            printf("ID_REMOTE_CONNECTION_LOST\n");
            break;
        case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
            printf("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
            break;
        case ID_CONNECTION_BANNED: // Banned from this server
            printf("We are banned from this server.\n");
            break;
        case ID_CONNECTION_ATTEMPT_FAILED:
            printf("Connection attempt failed\n");
            break;
        case ID_NO_FREE_INCOMING_CONNECTIONS:
            // Sorry, the server is full.  I don't do anything here but
            // A real app should tell the user
            printf("ID_NO_FREE_INCOMING_CONNECTIONS\n");
            break;

        case ID_INVALID_PASSWORD:
            printf("ID_INVALID_PASSWORD\n");
            break;

        case ID_CONNECTION_LOST:
            // Couldn't deliver a reliable packet - i.e. the other system was abnormally
            // terminated
            printf("ID_CONNECTION_LOST\n");
            break;

        case ID_CONNECTION_REQUEST_ACCEPTED:
            // This tells the client they have connected
            printf("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", m_packetPtr->systemAddress.ToString(true), m_packetPtr->guid.ToString());
            printf("My external address is %s\n", m_clientPtr->GetExternalID(m_packetPtr->systemAddress).ToString(true));
            break;
        case ID_CONNECTED_PING:
        case ID_UNCONNECTED_PING:
            printf("Ping from %s\n", m_packetPtr->systemAddress.ToString(true));
            break;


        case  SC_GET_HOUSES_LIST ://���ھ�����ģʽ��������ͻ��˷��ͷ����б�
            this->handleHouseList(&tempBitstream);
            break;
        case  SC_CREATE_HOUSE://���ھ�����ģʽ��������ͻ���֪ͨ�Լ��·��䴴���ɹ�
            this->handleNewHouseRequest();
            break;
        case  SC_LOGIN_HOUSE_ONE://���ھ�����ģʽ��������ͻ����Լ�����ĳ����ɹ�
            this->handleLoginRequsetOne(&tempBitstream);
            break;
        case  SC_LOGIN_HOUSE_TWO://���ھ�����ģʽ��������ͻ����Լ�����ĳ����ɹ�
            this->handleLoginRequsetTwo(&tempBitstream);
            break;
        case  SC_LOGIN_HOUSE_TO_OTHERONE://���ھ�����ģʽ��������ͻ���֪ͨĳ�����Ѿ���������
            this->handleOtherRoleJoin(&tempBitstream);
            break;
        case  SC_LOGOFF_HOUSE://���ھ�����ģʽ���������Լ�֪ͨ�Լ����ڵķ�������ĳĳ����
            this->handleOtherRoleLeave();
            break;


        default:
            // It's a client, so just show the message
            printf("%s\n", m_packetPtr->data);
            break;
        }
    }
}
unsigned char GetPacketIdentifier(RakNet::Packet *p)
{
    if (p == 0)
        return 255;

    if ((unsigned char)p->data[0] == ID_TIMESTAMP)
    {
        RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
        return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
    }
    else
        return (unsigned char) p->data[0];
}
ConnectManager *ConnectManager::instance = NULL;
ConnectManager *ConnectManager::GetInstance()
{
    if(instance == NULL)
    {
        instance = new ConnectManager();
    }
    return instance;
}
void ConnectManager::handleHouseList(RakNet::BitStream *tempBitStream)
{
    cout << "����houselist��" << endl;
    string tempHouseName;
    string tempHouseDancestyle;
    int tempHouseSite;

    //����һ��XML���ĵ�����
    TiXmlDocument myDocument;// = new TiXmlDocument();
    myDocument.LoadFile("houses.xml");
    //����һ����Ԫ�ز����ӡ�
    TiXmlElement *RootElement =  myDocument.RootElement();

    //////////////////////
    int i;
    tempBitStream->Read(i);
    if( i == 1)
    {
        tempBitStream->Read(tempHouseName);
        tempBitStream->Read(tempHouseDancestyle);
        tempBitStream->Read(tempHouseSite);

        //����һ��PersonԪ�ز����ӡ�
        TiXmlElement *PersonElement = new TiXmlElement("house");
        RootElement->LinkEndChild(PersonElement);
        //����PersonԪ�ص����ԡ�
        PersonElement->SetAttribute("name", tempHouseName.c_str());
        PersonElement->SetAttribute("dancestyle", tempHouseDancestyle.c_str());
        PersonElement->SetAttribute("site", tempHouseSite);
        //����nameԪ�ء�ageԪ�ز����ӡ�
    }
    myDocument.SaveFile("houses.xml");//���浽�ļ�

    this->mDancingGuiSys->setWidgetCreateHouse();

}
void ConnectManager::handleNewHouseRequest()
{
    cout << "�����½���������" << endl;
}
void ConnectManager::handleLoginRequsetTwo(RakNet::BitStream *tempBitStream)//SC_LOGIN_HOUSE
{
    string tempRoleName;
    bool   tempRoleSex;
    string tempRoleHire;
    string tempRoleDecorate;
    string tempRoleUpware;
    string tempRoleDownware;
    string tempRoleShoe;

    //����һ���û���Ϣ
    tempBitStream->Read(tempRoleName);
    tempBitStream->Read(tempRoleSex);
    tempBitStream->Read(tempRoleHire);
    tempBitStream->Read(tempRoleDecorate);
    tempBitStream->Read(tempRoleUpware);
    tempBitStream->Read(tempRoleDownware);
    tempBitStream->Read(tempRoleShoe);

    TiXmlDocument myDocument ;//= new TiXmlDocument();

    TiXmlElement *RootElement = new TiXmlElement("roles");
    myDocument.LinkEndChild(RootElement);

    TiXmlElement *PersonElement = new TiXmlElement("role");
    RootElement->LinkEndChild(PersonElement);

    PersonElement->SetAttribute("name", tempRoleName.c_str());
    PersonElement->SetAttribute("sex", tempRoleSex);
    PersonElement->SetAttribute("hire", tempRoleHire.c_str());
    PersonElement->SetAttribute("decorate", tempRoleDecorate.c_str() );
    PersonElement->SetAttribute("upware", tempRoleUpware.c_str());
    PersonElement->SetAttribute("downware", tempRoleDownware.c_str() );
    PersonElement->SetAttribute("downware", tempRoleShoe.c_str() );

    myDocument.SaveFile("otherrole.xml");
}
void ConnectManager::handleLoginRequsetOne(RakNet::BitStream *tempBitStream)//SC_LOGIN_HOUSE
{

    cout << "���ܼ��뷿������" << endl;
    string tempHouseName;
    string tempHouseDancestyle;
    string tempHouseDancemusic;
    string tempHouseDancescene;


    //������Ϣ
    tempBitStream->Read(tempHouseDancemusic);
    tempBitStream->Read(tempHouseDancescene);
    tempBitStream->Read(tempHouseDancestyle);
    tempBitStream->Read(tempHouseName);

    TiXmlDocument myDocument ;//= new TiXmlDocument();

    TiXmlElement *RootElement = new TiXmlElement("houses");
    myDocument.LinkEndChild(RootElement);

    TiXmlElement *PersonElement = new TiXmlElement("house");
    RootElement->LinkEndChild(PersonElement);

    PersonElement->SetAttribute("name", tempHouseName.c_str());
    PersonElement->SetAttribute("dancestyle", tempHouseDancestyle.c_str());
    PersonElement->SetAttribute("dancemusic", tempHouseDancemusic.c_str());
    PersonElement->SetAttribute("dancescene", tempHouseDancescene.c_str() );

    myDocument.SaveFile("myhouse.xml");

}
void ConnectManager::handleOtherRoleJoin(RakNet::BitStream *tempBitStream)
{
    cout << "������һ���û�������Ϣ��" << endl;

    string tempRoleName;
    bool   tempRoleSex;
    string tempRoleHire;
    string tempRoleDecorate;
    string tempRoleUpware;
    string tempRoleDownware;
    string tempRoleShoe;


    //����һ���û���Ϣ
    tempBitStream->Read(tempRoleName);
    tempBitStream->Read(tempRoleSex);
    tempBitStream->Read(tempRoleHire);
    tempBitStream->Read(tempRoleDecorate);
    tempBitStream->Read(tempRoleUpware);
    tempBitStream->Read(tempRoleDownware);
    tempBitStream->Read(tempRoleShoe);

    TiXmlDocument myDocument ;//= new TiXmlDocument();

    TiXmlElement *RootElement = new TiXmlElement("roles");
    myDocument.LinkEndChild(RootElement);

    TiXmlElement *PersonElement = new TiXmlElement("role");
    RootElement->LinkEndChild(PersonElement);

    PersonElement->SetAttribute("name", tempRoleName.c_str());
    PersonElement->SetAttribute("sex", tempRoleSex);
    PersonElement->SetAttribute("hire", tempRoleHire.c_str());
    PersonElement->SetAttribute("decorate", tempRoleDecorate.c_str() );
    PersonElement->SetAttribute("upware", tempRoleUpware.c_str());
    PersonElement->SetAttribute("downware", tempRoleDownware.c_str() );
    PersonElement->SetAttribute("downware", tempRoleShoe.c_str() );


    myDocument.SaveFile("otherrole.xml");
}
void ConnectManager::handleOtherRoleLeave()
{
    cout << "������һ���û��˳���Ϣ��" << endl;
    //delete mOtherRole;
    TiXmlDocument myDocument ;//= new TiXmlDocument();


    myDocument.SaveFile("otherrole.xml");

}


