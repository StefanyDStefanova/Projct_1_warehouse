#define _CRT_SECURE_NO_WARNINGS
#ifndef _MAIN_ACTION_IN_WAREHOUSE_H
#define _MAIN_ACTION_IN_WAREHOUSE_H

#include <iostream>
#include <fstream>  
#include <vector>   
#include <string>
#include "Product.cpp"

void mainActionInWarehouse() 
{
   std::vector <Product> products;
   String currLocation = "1/1/0"; //обозначава локацията на последния добавен продукт
   String flag = "repeat"; //обозначaва дали програмата трябва да бъде прекратена

    while (flag == "repeat") 
    {
       String command;
       std::cin >> command;
       if (command == "print") 
       {
            if (products.size() == 0) 
            { 
                std::cout << "There are not any products in warehouse!\n";
            }
            for (size_t i = 0; i < products.size(); i++) 
            {
                std::cout << products[i] << std::endl;
            }
        }
        else if (command == "add")
        {
            Product nProduct;
            std::cin >> nProduct;
            bool flag = false;
            for (size_t i = 0; i < products.size(); i++) 
            {
                if (products[i].getName() == nProduct.getName()) 
                {
                    flag = true;
                    if (products[i].getExpirationDate() == nProduct.getExpirationDate())
                    {
                        double currQuantity = products[i].getQuantity();
                        products[i].getQuantity(currQuantity + nProduct.getQuantity());
                    }
                    else 
                    {
                        Product temp;
                        temp.setLocation(currLocation);
                        nProduct.setLocation(nLocation(temp));
                        products.push_back(nProduct);
                        currLocation = nProduct.getLocation();
                    }
                }
            }
            if (flag == false) 
            {
                Product temp;
                temp.setLocation(currLocation);
                nProduct.setLocation(nLocation(temp));
                products.push_back(nProduct);
                currLocation = nProduct.getLocation();
            }
        }
        else if (command == "remove") 
        {
           String name;
           double quantity;
           std::cin >> name;
           std::cin >> quantity;
           for (size_t i = 0; i < products.size(); i++) {
               if (products[i].getName() == name) {
                   if (products[i].getQuantity() > quantity) 
                   {
                        double currQuantity = products[i].getQuantity();
                        products[i].setQuantity(currQuantity - quantity);
                   }
                   if (products[i].getQuantity() == quantity)
                   {
                        Product temp = products[i];
                        products.erase(products.begin() + i);
                        std::cout << temp << std::endl;
                   }
                    
                   if (products[i].getQuantity() < quantity) 
                   {
                        std::cout << "Insufficient quantity!" << std::endl;
                        for (size_t i = 0; i < products.size(); i++) 
                        {
                            if (products[i].getName() == name) 
                            {
                                std::cout << products[i].getName() << " ";
                                std::cout << products[i].getQuantity() << " ";
                                std::cout << products[i].getExpirationDate() << " ";
                            }
                        }
                    }
                }
            }
        }
        else if (command == "clean")
       {
            for (size_t i = 0; i < products.size(); i++) 
            {
                if (isExpiring(products[i])) 
                {
                    products.erase(products.begin() + i);
                }
            }
        }
        else if (command == "open") 
        {
           //String fileName;
           std::string fileName;
           std::cin >> fileName;
           std::ifstream in(fileName);
           
           if (!in.good()) 
           {
                std::ofstream out(fileName);
                out.close();
                std::cout << "File products.txt successfully created!" << std::endl;
            }
            else std::cout << "File products.txt successfully opend!" << std::endl;
            Product newProduct;
            in >> newProduct;
            while (in.good()) 
            {
                Product temp;
                temp.setLocation(currLocation);
                newProduct.setLocation(nLocation(temp));
                currLocation = newProduct.getLocation();
                products.push_back(newProduct);
                in >> newProduct;
            }
            in.close();
        }
        else if (command == "close") 
        {
           //String fileName;
           std::string fileName;
           std::cin >> fileName;
           std::fstream file(fileName);
            
           if (file.is_open()) 
           {
                file.close();
                std::cout << "Successfully closed " << fileName << "!" << std::endl;
           }
            else std::cout << "This file is already closed!" << std::endl;
        }
        else if (command == "save") 
        {
            std::ofstream out("products.txt");
            for (size_t i = 0; i < products.size(); i++) 
            {
                out << products[i].getName()
                    << " "
                    << products[i].getExpirationDate()
                    << " "
                    << products[i].getEntranceDate()
                    << " "
                    << products[i].getProducer()
                    << " "
                    << products[i].getUnit()
                    << " "
                    << products[i].getQuantity()
                    << " "
                    << products[i].getComment()
                    << std::endl;
            }
            std::cout << "Successfully saved products.txt!" << std::endl;
        }
        else if (command == "saveas") {
           //String fileName;
           std::string fileName;
           std::cin >> fileName;
           if (fileName.find("product") != std::string::npos) 
           {
                std::ofstream out(fileName);
                for (size_t i = 0; i < products.size(); i++) {
                    out << products[i].getName()
                        << " "
                        << products[i].getExpirationDate()
                        << " "
                        << products[i].getEntranceDate()
                        << " "
                        << products[i].getProducer()
                        << " "
                        << products[i].getUnit()
                        << " "
                        << products[i].getQuantity()
                        << " "
                        << products[i].getComment()
                        << std::endl;
                }
            }
            else std::cout << "Wrong file name!" << std::endl;
        }
        else if (command == "help") {
            std::cout << "The following commands are supported: " << std::endl;
            std::cout << "open <file>                  opens <file>" << std::endl;
            std::cout << "close                        closes currently open file" << std::endl;
            std::cout << "save                         saves the currently open file" << std::endl;
            std::cout << "saveas <file>                saves the currently open file in <file>" << std::endl;
            std::cout << "help                         prits this information" << std::endl;
            std::cout << "exit                         exits the program" << std::endl;
            std::cout << "print                        prints information about all products" << std::endl;
            std::cout << "add                          adds a new product" << std::endl;
            std::cout << "remove                       removes a product" << std::endl;
            std::cout << "clean                        removes all product with expiration date" << std::endl;
        }
        else if (command == "exit") 
        {
            std::cout << "Exiting programm." << std::endl;
            flag = "end";
        }
        else std::cout << "Invalid command!" << std::endl;
    }
}

#endif