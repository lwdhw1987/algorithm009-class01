import java.util.Deque;

public class DequeCode {

    public static void main(String[] args) {
        dequeNew();
    }

    private static void dequeNew(){
        Deque<String> deque = new LinkedList<>();
        deque.addFirst("a");
        deque.addFirst("b");
        deque.addFirst("c");
        System.out.println(deque);

        String str = deque.getFirst();
        System.out.println(str);
        System.out.println(deque);

        while(deque.size() > 0){
            System.out.println(deque.pollFirst());
        }
        System.out.println(deque);
    }
}
