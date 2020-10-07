#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <queue>
#include "event.hpp"
#include "figures.hpp"
#include "event_loop.hpp"

int main(int argc, char *argv[]){
	if(argc != 2){
		std::cout << "usage:" << argv[0] << " BUFFER_SIZE\n";
		return 0;
	}

	int buffer_size = std::atoi(argv[1]);
	std::vector<std::shared_ptr<IFigure>> shapes;
	EventLoop eventLoop;
	std::shared_ptr<IHandler> handlerPrinter(new HandlerPrinter());
	std::shared_ptr<IHandler> handlerLogger(new HandlerLogger());
	eventLoop.addHandler(EventType::print, handlerPrinter);
	eventLoop.addHandler(EventType::log, handlerLogger);
	RhombusFactory rhombusFactory;
	PentagonFactory pentagonFactory;
	HexagonFactory hexagonFactory;
	std::string cmd;
	int id = 1;

	std::thread thHandler(std::ref(eventLoop));
	while(std::cin >> cmd){
		if(cmd == "quit"){
			Event ev = Event(EventType::quit, std::make_shared<EventData>(), std::make_shared<EventContext>(), [](auto){});
			eventLoop.addEvent(ev);
			break;
		}else if(cmd == "create"){
			std::string type;
			std::pair<double, double> center;
			std::pair<double, double> point;
			std::cin >> type >> center.first >> center.second >> point.first >> point.second;
			if(type == "rhombus"){
				shapes.push_back(rhombusFactory.FigureCreate(id, center, point));
			}else if(type == "pentagon"){
				shapes.push_back(pentagonFactory.FigureCreate(id, center, point));
			}else if(type == "hexagon"){
				shapes.push_back(hexagonFactory.FigureCreate(id, center, point));
			}else{
				std::cerr << "Error: incorrect figure type" << std::endl;
				continue;
			}
			++id;
			std::cout << "Figure added\n";
		}
		bool printer_done = false;
		bool context_done = false;
		if(shapes.size() == buffer_size){
			Event ev1 = Event(EventType::print, 
				std::make_shared<EventDataPrinter>(shapes),
				std::make_shared<EventContextPrinter>(printer_done),
				[](std::shared_ptr<EventContext> cnt){
					if(auto ptr = std::static_pointer_cast<EventContextPrinter>(cnt))
                		ptr->done = true;
				});
			Event ev2 = Event(EventType::log,
				std::make_shared<EventDataLogger>(shapes),
				std::make_shared<EventContextLogger>(context_done),
				[](std::shared_ptr<EventContext> cnt){
					if(auto ptr = std::static_pointer_cast<EventContextPrinter>(cnt))
                		ptr->done = true;
				});
			eventLoop.addEvent(ev1);
			eventLoop.addEvent(ev2);
			while(!printer_done && !context_done){
				std::cout << '.' << std::flush;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
			shapes.resize(0);
		}
	}
	thHandler.join();
	return 0;
}
