#include "network.h"
//#include "user.h"


network :: ~network()
{
    for (int i = 0; i < users_.size(); i++)
    {
        delete users_[i];
    }
    users_.clear();
}


void network :: addUser(user* u)
{
    users_.push_back(u);
}

int network :: addConnection(std::string s1, std::string s2)
{
    std::size_t i1 = getId(s1);
    std::size_t i2 = getId(s2);

    if(i1 == i2)
    {
        return -1;
    }
    else
    {
        user* temp = getUser(i1);
        user* temp2 = getUser(i2);

        temp->addFriend(i2);
        temp2->addFriend(i1);

        return 0;
    }
}

int network :: removeConnection(std::string s1, std::string s2)
{
    std::size_t i1 = getId(s1);
    std::size_t i2 = getId(s2);
    if(i1 == i2)
    {
        return -1;
    }
    else
    {
        user* temp = getUser(i1);
        user* temp2 = getUser(i2);

        bool f = false;
        std::vector<std::size_t> u1f = temp->getFriends();
        for(int i = 0; i < u1f.size(); i++)
        {
            if(u1f[i] == i2)
                f = true;

        }
        if(f == true)
        {
            temp->deleteFriend(i2);
            temp2->deleteFriend(i1);
            return 0;
        }
        else
        {
            return -1;
        }
    }


}

int network :: readUsers(const char* fname)
{
    std::ifstream f(fname);

    if(!f.is_open())
    {
        return -1;
    }

    std::string nUs;
    getline(f, nUs);
    std::string name, sId, sYear, sZip;

    std::vector<std::size_t> users;

    for(int i = 0; i < stoi(nUs); i++)
    {
        getline(f, sId);
        f.ignore();
        getline(f, name);
        getline(f, sYear);
        getline(f, sZip);
        std::string l;
        getline(f, l);
        std::stringstream ss(l);
        std::vector<std::size_t> tempV;
        std::size_t v;
        while (ss >> v)
        {
            tempV.push_back(v);
        }

        user* u = new user(stoul(sId), name, stoul(sYear), stoul(sZip), tempV);
        addUser(u);
    }

    f.close();
    return 0;
}


int network :: writeUsers(const char *fname)
{
    std::ofstream f;
    f.open(fname);
    if(!f.is_open())
        return -1;
    f << users_.size() << '\n';
    for(int i = 0; i < users_.size(); i++)
    {
        f << users_[i]->getId() << '\n';
        f << '\t' << users_[i]->getName() << '\n';
        f << '\t' << users_[i]->getYear() << '\n';
        f << '\t' << users_[i]->getZip() << '\n';
        f << '\t';
        std::vector<std::size_t> temp = users_[i]->getFriends();
        for(int k = 0; k < temp.size(); k++)
        {
            f << temp[k] << ' ';
        }
        f << '\n';
    }

    f.close();
    return 0;
}

std::size_t network :: getId(std::string n)
{
    for(std::size_t k = 0; k < users_.size(); k++)
    {

        std::string nm = users_[k]->getName();
        if(nm == n)
        {
            return users_[k]->getId();
        }
    }
    return -1;
}

user* network :: getUser(std::size_t id)
{
    for(int i = 0; i<users_.size(); i++)
    {
        if(users_[i]->getId() == id)
        {
            return users_[i];
        }
    }
    return nullptr;
}

std::vector<std::size_t> network::shortestPath(std::size_t from, std::size_t to)
{
    std::queue<std::size_t> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<std::size_t> d(users_.size(), -1);

    d[from] = 0;
    q.push(from);
    while (!q.empty())
    {
        std::size_t temp = q.front();
        q.pop();

        if (visited[temp])
            continue;

        visited[temp] = true;

        std::vector<std::size_t> f = users_[temp]->getFriends();
        for (int i = 0; i < f.size(); i++)
        {
            std::size_t id = f[i];

            if (!visited[id] && d[id] == -1)
            {
                q.push(id);
                d[id] = temp;
            }

        }

    }
    std::vector<std::size_t> path;
    std::size_t curr = to;
    while (curr != from)
    {
        path.push_back(curr);
        curr = d[curr];
    }
    path.push_back(from);
    reverse(path.begin(), path.end());

    return path;

}

std::vector<std::size_t> network::distanceUser(std::size_t from, std::size_t& to, std::size_t distance)
{
    std::vector<std::size_t> path = shortestPath(from, to);


    if(path.size()-1 == distance)
    {
        return path;
    }
    else
    {
        to = -1;
        return std::vector<std::size_t>();
    }

}

std::vector<std::size_t> network::suggestFriends(std::size_t who, std::size_t& score)
{
    std::vector<std::size_t> rec;
    std::unordered_map<std::size_t, std::size_t> sc;
    size_t max = 0;

    for(std::size_t i = 0; i < users_.size(); i++)
    {
        user* temp = getUser(i);
        if (shortestPath(who, temp->getId()).size() == 3)
        {
            rec.push_back(temp->getId());
        }
    }

    for (std::size_t ff : rec)
    {
        if (ff != who)
        {
            std::vector<std::size_t> fFriends = getUser(ff)->getFriends();
            std::vector<std::size_t> tFriends = getUser(who)->getFriends();

            for (std::size_t uf : fFriends)
            {
                if (uf != who && std::find(tFriends.begin(), tFriends.end(), uf) == tFriends.end())
                //if (uf != who )
                {
                    sc[uf]++;
                }
            }
        }
    }

    for (const auto& e : sc)
    {
        if (e.second > max)
        {
            max = e.second;
        }
    }

    score = max;

    std::vector<std::size_t> sug;
    for (const auto& e : sc)
    {
        if (e.second == max) {
            sug.push_back(e.first);
        }
    }

    return sug;

}



std::vector<std::vector<std::size_t>> network::groups()
{
    std::vector<std::vector<std::size_t>> sets;
    std::vector<bool> visited(users_.size(), false);

    for (int i = 0; i < users_.size(); i++)
    {
        if (!visited[i])
        {
            std::vector<std::size_t> curr;
            DFS(i, visited, curr);

            sets.push_back(curr);
        }
    }

    return sets;
}


void network::DFS(std::size_t id, std::vector<bool>& visited, std::vector<std::size_t>& curr)
{
    visited[id] = true;
    curr.push_back(id);

    std::vector<std::size_t> friends = users_[id]->getFriends();
    for (std::size_t friendId : friends)
    {
        if (!visited[friendId])
        {
            DFS(friendId, visited, curr);
        }
    }
}


void network :: addPost(std::size_t ownerId, std::string message, std::size_t likes, bool incoming, std::size_t author, bool isPublic)
{
    user* owner = users_[ownerId];

    if(incoming) // checks if it's an incoming post
    {
        std::string auth = users_[author]->getName(); // gets author name
        IncomingPost *newP = new IncomingPost(ownerId, message, likes, auth, isPublic); // creates IncomingPost obj with given parameters
        owner->addPost(newP); // adds incoming post to owners messages vector

    }
    else
    {
        Post *newP = new Post(ownerId, message, likes); // creates regular post object
        owner->addPost(newP); // adds post to owners messages vector
    }

}

std::string network :: displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic)
{
    std::size_t temp = getId(name); // gets user ID
    user* curr = users_[temp]; //gets user object from ID
    std::string str = curr->displayPosts(howMany, showOnlyPublic); // calls users indviidual display posts function
    return str;
}


int network :: readPosts(std::string name, const char* fname)
{

    int ownerId = getId(name);
    user* owner = users_[ownerId];
    std::ifstream f(fname);

    if(!f.is_open())
    {
        return -1;
    }
    std::string nPosts;
    getline(f, nPosts);
    std::string pNum, msg, uId, likes, pub, auth;
    std::string temp;

    getline(f, pNum);
    for(int i = 0; i < stoi(nPosts); i++)
    {
        f.ignore();
        getline(f, msg);
        f.ignore();
        getline(f, uId);
        f.ignore();
        getline(f, likes);
        getline(f, temp);
        if(temp == "\tpublic")
        {
            pub = temp;
            f.ignore();
            getline(f, auth);
            IncomingPost *newP = new IncomingPost(ownerId, msg, std::stoi(likes), auth, 1);
            owner->addPost(newP);
            getline(f, pNum);
        }
        else if(temp == "\tprivate")
        {
            pub = temp;
            f.ignore();
            getline(f, auth);
            IncomingPost *newP = new IncomingPost(ownerId, msg, std::stoi(likes), auth, 0);
            owner->addPost(newP);
            getline(f, pNum);
        }
        else
        {
            getline(f, pNum);
            Post *newP = new Post(ownerId, msg, std::stoi(likes));
            owner->addPost(newP);
        }

    }


    return 0;
}
